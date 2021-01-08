#include "Benchmark.h"
#include "OpensslSinkFactory.h"
#include "SinkImpl.h"
#include "TransparentSinkFactory.h"

using namespace std;

int main(int, char **)
{
	Benchmark(
		make_shared<SinkImpl>(make_shared<TransparentSinkFactory>()),
		make_shared<SinkImpl>(make_shared<OpensslSinkFactory>())
	).run();
	return 0;
}
