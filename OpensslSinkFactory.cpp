#include "OpensslSinkFactory.h"

using namespace std;

string OpensslSinkFactory::name() const
{
	return "Openssl";
}

shared_ptr<const goost::Sink> OpensslSinkFactory::sink(
	const shared_ptr<const goost::Sink> &under
) const
{
	return under;
}
