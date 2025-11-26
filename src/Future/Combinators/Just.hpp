#pragma once

#include <variant>

namespace renn {

/*
 * => An approach to initialize async pipeline
 */

using Unit = std::monostate;

inline constexpr Unit unit = Unit{};

};  // namespace renn
