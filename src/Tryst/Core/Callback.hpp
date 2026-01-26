#pragma once

#include "../../Utils/Result.hpp"
#include <function2/function2.hpp>

namespace renn::tryst {

template <typename T>
using Callback = fu2::unique_function<void(T)>;

template <typename T>
using UnpackedCallback = fu2::unique_function<void(utils::Result<T>)>;

};  // namespace renn::tryst
