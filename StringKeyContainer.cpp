#include "StringKeyContainer.h"
#include <goost/magma/LazyKey.h>

using namespace std;
using namespace goost;

StringKeyContainer::StringKeyContainer(const string &data)
	: data(data)
{
}

shared_ptr<const magma::Key> StringKeyContainer::key() const
{
	return make_shared<magma::LazyKey>(data);
}
