#include "Benchmark.h"
#include <iostream>
#include "Impl.h"

using namespace std;

void Benchmark::run() const
{
	for (const auto &i : impls) {
		const size_t datasize = 1024 * 1024 * 64;
		const auto time = i->run(datasize, 1024);
		const size_t throughput = datasize * 8 / time.count() / 1024;
		cout << i->name() << ": " << throughput << " Kbps" << endl;
	}
}
