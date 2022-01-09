#pragma once
#include <string>
#include "KeyContainer.h"

class StringKeyContainer final : public KeyContainer {
public:
	explicit StringKeyContainer(const std::string &data);

	std::shared_ptr<const goost::magma::Key> key() const override;
private:
	const std::string data;
};
