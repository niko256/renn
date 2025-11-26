#pragma once

#include "Future.hpp"

namespace renn {

template <typename T>
auto get() -> Future<utils::Result<T>>;

};
