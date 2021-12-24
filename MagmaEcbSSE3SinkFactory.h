#pragma once
#include "SinkFactory.h"

class MagmaEcbSSE3SinkFactory final : public SinkFactory {
public:
	std::string name() const override;
	std::shared_ptr<const goost::Sink> sink(
		const std::shared_ptr<const goost::Sink> &under
	) const override;
};
