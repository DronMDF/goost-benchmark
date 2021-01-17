#include "NullSink.h"

using namespace std;

shared_ptr<const goost::Sink> NullSink::write(const vector<byte> &data [[maybe_unused]]) const
{
	return make_shared<NullSink>();
}

shared_ptr<const goost::Sink> NullSink::finalize() const
{
	return make_shared<NullSink>();
}
