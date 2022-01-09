#include "SSE3Alg.h"
#include "SSE3EcbIOFactory.h"

using namespace std;

SSE3Alg::SSE3Alg(const shared_ptr<const KeyContainer> &container)
	: container(container)
{
}

shared_ptr<const IOFactory> SSE3Alg::ecb() const
{
	return make_shared<SSE3EcbIOFactory>(container);
}
