#pragma once

#include "../Core/Future.hpp"
#include "../Termination/Get.hpp"
#include "../Trait/ValueOf.hpp"

namespace renn::future {

template <SomeFuture F>
auto Get(F thunk) -> trait::ValueOf<F> {
    thunk::Receiver<F> getter{std::move(thunk)};
    return getter.get();
}

}  // namespace renn::future
