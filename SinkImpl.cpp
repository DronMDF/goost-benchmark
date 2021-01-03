#include "SinkImpl.h"
#include <vector>
#include "MemorySink.h"
#include "SinkFactory.h"

using namespace std;

SinkImpl::SinkImpl(const shared_ptr<const SinkFactory> &factory)
	: factory(factory)
{
}

string SinkImpl::name() const
{
	return factory->name();
}

chrono::duration<double> SinkImpl::run(const size_t data_size, const size_t block_size) const
{
	size_t size = 0;
	vector<byte> block(min(block_size, data_size), byte());
	auto sink = factory->sink(make_shared<MemorySink>());
	const auto start_time = chrono::high_resolution_clock::now();
	while (size < data_size) {
		sink = sink->write(block);
		size += block.size();
	}
	sink->finalize();
	const auto end_time = chrono::high_resolution_clock::now();
	return end_time - start_time;
}
