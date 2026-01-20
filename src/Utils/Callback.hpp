#pragma once

#include "Result.hpp"
#include "function2/function2.hpp"

namespace renn::utils {

template <typename T>
using Callback = fu2::unique_function<void(utils::Result<T>)>;

};
