#include "MemorySink.h"

using namespace std;
using namespace goost;

MemorySink::MemorySink(const vector<byte> &data)
	: data(data)
{
}

MemorySink::MemorySink()
	: MemorySink(vector<byte>{})
{
}

shared_ptr<const Sink> MemorySink::write(const vector<byte> &d) const
{
	auto dd = data;
	dd.insert(dd.end(), d.begin(), d.end());
	return make_shared<MemorySink>(dd);
}

shared_ptr<const Sink> MemorySink::finalize() const
{
	return make_shared<MemorySink>(data);
}

vector<byte> MemorySink::raw() const
{
	return data;
}
