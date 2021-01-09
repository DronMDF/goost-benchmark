#include "MagmaCfbSinkFactory.h"
#include <goost/magma/CFBSink.h>
#include <goost/magma/Key.h>

using namespace std;
using namespace goost;

string MagmaCfbSinkFactory::name() const
{
	return "Magma CFB";
}

shared_ptr<const goost::Sink> MagmaCfbSinkFactory::sink(
	const shared_ptr<const goost::Sink> &under
) const
{
	return make_shared<magma::CFBSink>(
		under,
		make_shared<magma::Key>(
			"ffeeddccbbaa99887766554433221100"
			"f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff"
		),
		0x1234567890abcdef,
		0x234567890abcdef1
	);
}
