#pragma once
#include <memory>

namespace goost {
	class Sink;
	class Source;
}

class IOFactory {
public:
	virtual ~IOFactory() = default;

	virtual std::shared_ptr<const goost::Sink> sink(
		const std::shared_ptr<const goost::Sink> &next
	) const = 0;

	virtual std::shared_ptr<const goost::Source> source(
		const std::shared_ptr<const goost::Source> &next
	) const = 0;
};
