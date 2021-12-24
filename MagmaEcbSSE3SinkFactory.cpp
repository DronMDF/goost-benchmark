#include "MagmaEcbSSE3SinkFactory.h"
#include <goost/magma/ECBSink.h>
#include <goost/magma/LazyKey.h>

using namespace std;
using namespace goost;

string MagmaEcbSSE3SinkFactory::name() const
{
	return "Magma ECB SSE3 (in progress)";
}

shared_ptr<const goost::Sink> MagmaEcbSSE3SinkFactory::sink(
	const shared_ptr<const goost::Sink> &under
) const
{
	return make_shared<magma::ECBSink>(
		under,
		make_shared<magma::LazyKey>(
			"ffeeddccbbaa99887766554433221100"
			"f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
		)
	);
}
