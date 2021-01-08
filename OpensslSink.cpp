#include "OpensslSink.h"
#include <stdexcept>

using namespace std;

OpensslSink::OpensslSink(const shared_ptr<const goost::Sink> &sink, EVP_CIPHER_CTX * const ctx)
	: sink(sink), ctx(ctx)
{
}

shared_ptr<const goost::Sink> OpensslSink::write(const vector<byte> &data) const
{
	vector<byte> ctext(data.size() + 16);
	int out_len = ctext.size();
	int rc = EVP_EncryptUpdate(
		ctx,
		reinterpret_cast<unsigned char *>(&ctext[0]), &out_len,
		reinterpret_cast<const unsigned char *>(&data[0]), data.size()
	);
	if (rc != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw runtime_error("EVP_EncryptUpdate failed");
	}
	ctext.resize(out_len);
	return make_shared<OpensslSink>(sink->write(ctext), ctx);
}

shared_ptr<const goost::Sink> OpensslSink::finalize() const
{
	vector<byte> ctext(16);
	int out_len = ctext.size();
	int rc = EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char *>(&ctext[0]), &out_len);
	if (rc != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw runtime_error("EVP_EncryptFinal_ex failed");
	}
	ctext.resize(out_len);
	sink->write(ctext);
	EVP_CIPHER_CTX_free(ctx);
	return sink;
}
