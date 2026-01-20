#pragma once

#include "../../Runtime/Core/State.hpp"

namespace renn::future {

template <typename C, typename V>
concept Continuation = requires(C cont, V v, rt::State st) {
    { cont.proceed(std::move(v), st) };
};

}  // namespace renn::future
