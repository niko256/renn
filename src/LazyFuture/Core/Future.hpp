#pragma once

#include "Thunk.hpp"
#include <concepts>

namespace renn::future {

template <typename F>
concept SomeFuture = thunk::Thunk<F>;

template <typename F, typename V>
concept Future = SomeFuture<F> && std::same_as<typename F::ValueType, V>;

}  // namespace renn::future
