#pragma once
#include <memory>
#include "Impl.h"

class SinkFactory;

class SinkImpl final : public Impl {
public:
	explicit SinkImpl(const std::shared_ptr<const SinkFactory> &factory);
	std::string name() const override;
	std::chrono::duration<double> run(
		const size_t data_size,
		const size_t block_size
	) const override;
private:
	const std::shared_ptr<const SinkFactory> factory;
};
