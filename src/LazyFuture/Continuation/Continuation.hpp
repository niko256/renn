#pragma once

#include <concepts>
#include "Continuation.hpp"
#include "../../Infra/Core/Env.hpp"

namespace renn::future::role {

struct ContinuationTag {};

}  // namespace renn::future::role

namespace renn::future {

template <typename C, typename V>
concept Continuation
    = std::derived_from<C, role::ContinuationTag> && requires(C cont, V v, rt::Env st) {
          { cont.proceed(std::move(v), st) };
      };

}  // namespace renn::future
