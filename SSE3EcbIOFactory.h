#pragma once
#include "IOFactory.h"

class KeyContainer;

class SSE3EcbIOFactory final : public IOFactory {
public:
	explicit SSE3EcbIOFactory(const std::shared_ptr<const KeyContainer> &container);

	std::shared_ptr<const goost::Sink> sink(
		const std::shared_ptr<const goost::Sink> &next
	) const override;

	std::shared_ptr<const goost::Source> source(
		const std::shared_ptr<const goost::Source> &next
	) const override;

private:
	const std::shared_ptr<const KeyContainer> container;
};
