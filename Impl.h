#pragma once
#include <chrono>
#include <string>

class Impl {
public:
	virtual ~Impl() = default;

	virtual std::string name() const = 0;

	// @todo Need compare result between different implementation
	virtual std::chrono::duration<double> run(
		const size_t data_size,
		const size_t block_size
	) const = 0;
};
