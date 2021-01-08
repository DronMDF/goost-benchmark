#include <stdexcept>
#include <openssl/engine.h>
#include "Benchmark.h"
#include "OpensslSinkFactory.h"
#include "SinkImpl.h"
#include "TransparentSinkFactory.h"

using namespace std;

int main(int, char **)
{
	OPENSSL_add_all_algorithms_conf();
	ERR_load_crypto_strings();

	ENGINE *eng = ENGINE_by_id("gost");
	if (eng == nullptr) {
		throw runtime_error("No engine");
	}
	ENGINE_init(eng);
	ENGINE_set_default(eng, ENGINE_METHOD_ALL);

	Benchmark(
		make_shared<SinkImpl>(make_shared<TransparentSinkFactory>()),
		make_shared<SinkImpl>(make_shared<OpensslSinkFactory>())
	).run();
	return 0;
}
