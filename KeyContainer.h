#pragma once
#include <memory>

namespace goost {
namespace magma {
class Key;
}
}

class KeyContainer {
public:
	virtual ~KeyContainer() = default;

	// TODO: Необходимо продумать как получать из одной и той же ключевой информации
	// ключи разных типов (оптимизированные для разных CPU).
	virtual std::shared_ptr<const goost::magma::Key> key() const = 0;
};
