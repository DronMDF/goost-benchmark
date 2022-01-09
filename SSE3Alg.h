#pragma once
#include <memory>

class IOFactory;
class KeyContainer;

class SSE3Alg final {
public:
	explicit SSE3Alg(const std::shared_ptr<const KeyContainer> &container);

	std::shared_ptr<const IOFactory> ecb() const;

private:
	const std::shared_ptr<const KeyContainer> container;
};
