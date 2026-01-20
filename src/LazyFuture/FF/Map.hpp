#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Map.hpp"
#include <utility>

namespace renn::future {

namespace pipe {

template <typename F>
struct [[nodiscard]] Map {
    F procedure_;

    explicit Map(F user);

    Map(const Map&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename F>
Map<F>::Map(F user) : procedure_(std::move(user)) {}

template <typename F>
template <SomeFuture Input>
SomeFuture auto Map<F>::pipe(Input in) {
    return thunk::Map{std::move(in), std::move(procedure_)};
}

}  // namespace pipe

template <typename F>
auto Map(F proc) {
    return pipe::Map<F>{std::move(proc)};
}

}  // namespace renn::future
