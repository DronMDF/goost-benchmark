#include "MemorySink.h"

using namespace std;
using namespace goost;

MemorySink::MemorySink(const list<vector<byte>> &data)
	: data(data)
{
}

MemorySink::MemorySink()
	: MemorySink(list<vector<byte>>{})
{
}

shared_ptr<const Sink> MemorySink::write(const vector<byte> &d) const
{
	auto dd = data;
	dd.push_back(d);
	return make_shared<MemorySink>(dd);
}

shared_ptr<const Sink> MemorySink::finalize() const
{
	return make_shared<MemorySink>(data);
}

vector<byte> MemorySink::raw() const
{
	vector<byte> rv;
	for (const auto &d : data) {
		rv.insert(rv.end(), d.begin(), d.end());
	}
	return rv;
}
