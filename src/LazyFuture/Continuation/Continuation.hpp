#pragma once

#include "../../Runtime/Core/State.hpp"
#include <concepts>
#include "Continuation.hpp"

namespace renn::future::role {

struct ContinuationTag {};

}  // namespace renn::future::role

namespace renn::future {

template <typename C, typename V>
concept Continuation = std::derived_from<C, role::ContinuationTag>
                       && requires(C cont, V v, rt::State st) {
                              { cont.proceed(std::move(v), st) };
                          };

}  // namespace renn::future
