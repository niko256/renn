#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Get.hpp"
#include "../Trait/ValueOf.hpp"

namespace renn::future {

template <SomeFuture F>
auto Get(F thunk) -> trait::ValueOf<F> {
    thunk::Getter<F> getter{std::move(thunk)};
    return getter.get();
}

}  // namespace renn::future
