#pragma once
#include <list>
#include <goost/Sink.h>

class MemorySink final : public goost::Sink {
public:
	explicit MemorySink(const std::list<std::vector<std::byte>> &data);
	MemorySink();

	std::shared_ptr<const goost::Sink> write(const std::vector<std::byte> &data) const override;
	std::shared_ptr<const goost::Sink> finalize() const override;

	std::vector<std::byte> raw() const;
private:
	const std::list<std::vector<std::byte>> data;
};
