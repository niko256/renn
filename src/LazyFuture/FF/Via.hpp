#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Future.hpp"
#include "../Thunks/Via.hpp"
#include "Core/IExecutor.hpp"

namespace renn::future {

namespace pipe {

struct [[nodiscard]] ViaCombinator {
    rt::View runtime_;

    explicit ViaCombinator(rt::View rt);

    ViaCombinator(const ViaCombinator&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

ViaCombinator::ViaCombinator(rt::View rt)
    : runtime_(rt) {}

template <SomeFuture Input>
SomeFuture auto ViaCombinator::pipe(Input in) {
    return thunk::Via{std::move(in), runtime_};
}

}  // namespace pipe

inline auto Via(rt::View runtime) {
    return pipe::ViaCombinator{runtime};
}

inline auto Via(rt::IExecutor& exe) {
    return pipe::ViaCombinator{rt::make_view(exe)};
}

}  // namespace renn::future
