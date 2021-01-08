#include "OpensslSinkFactory.h"
#include <stdexcept>
#include "OpensslSink.h"

using namespace std;

string OpensslSinkFactory::name() const
{
	return "Openssl";
}

shared_ptr<const goost::Sink> OpensslSinkFactory::sink(
	const shared_ptr<const goost::Sink> &under
) const
{
        const EVP_CIPHER *type = EVP_get_cipherbynid(NID_gost89_cbc);
        if (type == nullptr) {
        	throw runtime_error("No encrypt ciphers");
	}

	uint8_t key[32] = {
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7
	};
	uint8_t iv[16] = {
		0, 1, 2, 3, 4, 5, 6, 7,
		0, 1, 2, 3, 4, 5, 6, 7
	};

	auto * const ctx = EVP_CIPHER_CTX_new();
	int rc = EVP_EncryptInit_ex(ctx, type, NULL, key, iv);
	if (rc != 1) {
		EVP_CIPHER_CTX_free(ctx);
		throw runtime_error("EVP_EncryptInit_ex failed");
	}

	return make_shared<OpensslSink>(under, ctx);
}
