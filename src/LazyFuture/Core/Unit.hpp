#pragma once

#include <variant>

namespace renn::future {

using Unit = std::monostate;

inline constexpr Unit unit = Unit{};

}  // namespace renn::future
