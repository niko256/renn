#pragma once

#include <variant>


using Unit = std::monostate;

inline constexpr Unit unit = Unit{};
