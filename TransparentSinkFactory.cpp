#include "TransparentSinkFactory.h"

using namespace std;
using namespace goost;

string TransparentSinkFactory::name() const
{
	return "Transparent";
}

shared_ptr<const Sink> TransparentSinkFactory::sink(const shared_ptr<const Sink> &under) const
{
	return under;
}
