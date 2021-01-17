#pragma once
#include <list>
#include <goost/Sink.h>

class NullSink final : public goost::Sink {
public:
	std::shared_ptr<const goost::Sink> write(const std::vector<std::byte> &data) const override;
	std::shared_ptr<const goost::Sink> finalize() const override;
};
