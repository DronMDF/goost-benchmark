#pragma once
#include <goost/Sink.h>
#include <openssl/evp.h>

class OpensslSink final : public goost::Sink {
public:
	OpensslSink(const std::shared_ptr<const goost::Sink> &sink, EVP_CIPHER_CTX * const ctx);

	std::shared_ptr<const goost::Sink> write(const std::vector<std::byte> &data) const override;
	std::shared_ptr<const goost::Sink> finalize() const override;
private:
	const std::shared_ptr<const goost::Sink> sink;
	EVP_CIPHER_CTX * const ctx;
};
