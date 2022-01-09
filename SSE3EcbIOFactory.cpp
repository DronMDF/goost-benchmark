#include "SSE3EcbIOFactory.h"
#include <stdexcept>
#include <goost/magma/ECBSink.h>
#include "KeyContainer.h"

using namespace std;
using namespace goost;

SSE3EcbIOFactory::SSE3EcbIOFactory(const shared_ptr<const KeyContainer> &container)
	: container(container)
{
}

shared_ptr<const Sink> SSE3EcbIOFactory::sink(const shared_ptr<const Sink> &next) const
{
	// TODO: Нужно использовать оптимизированный для SSE3 ECBSink
	return make_shared<magma::ECBSink>(next, container->key());
}

shared_ptr<const Source> SSE3EcbIOFactory::source(
	const shared_ptr<const Source> &next [[maybe_unused]]
) const
{
	throw runtime_error("Not implement");
}
