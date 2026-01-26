#pragma once

#include <exception>
#include <expected>

namespace renn::utils {

template <typename T, typename E = std::exception_ptr>
using Result = std::expected<T, E>;

};
