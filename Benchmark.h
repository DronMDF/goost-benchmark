#pragma once
#include <memory>
#include <vector>

class Impl;

// This class run different implementation with some data
// Each Implemetation run with different block size
// for check cache affinity
class Benchmark final {
public:
	explicit Benchmark(const std::shared_ptr<const Impl> &impl);
	void run() const;
private:
	const std::vector<std::shared_ptr<const Impl>> impls;
};
