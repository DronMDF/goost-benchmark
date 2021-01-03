#include "Benchmark.h"
#include <iostream>
#include "Impl.h"

using namespace std;

Benchmark::Benchmark(const std::shared_ptr<const Impl> &impl)
	: impls(1, impl)
{
}

void Benchmark::run() const
{
 	for (int bs = 20; bs < 28; bs++) {
		for (const auto &i : impls) {
			const size_t datasize = 1024 * 1024 * 64;
			const auto time = i->run(datasize, 1 << bs);
			const size_t throughput = datasize * 8 / time.count() / (1024 * 1024);
			cout << i->name() << ": " << datasize << " bytes, " << time.count() << " sec" << endl;
			cout << i->name() << ": " << throughput << " Mbps" << endl;
		}
	}
}
