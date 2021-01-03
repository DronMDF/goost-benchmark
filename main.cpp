#include "Benchmark.h"
#include "SinkImpl.h"
#include "TransparentSinkFactory.h"

using namespace std;

int main(int, char **)
{
	Benchmark(
		make_shared<SinkImpl>(
			make_shared<TransparentSinkFactory>()
		)
	).run();
	return 0;
}
