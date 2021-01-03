#pragma once
#include <string>
#include <memory>
#include <goost/Sink.h>

class SinkFactory {
public:
	virtual ~SinkFactory() = default;

	virtual std::string name() const = 0;
	virtual std::shared_ptr<const goost::Sink> sink(
		const std::shared_ptr<const goost::Sink> &under
	) const = 0;
};
