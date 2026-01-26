#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Map.hpp"
#include <utility>

namespace renn::future {

namespace pipe {

template <typename F>
struct [[nodiscard]] MapCombinator {
    F procedure_;

    explicit MapCombinator(F user);

    MapCombinator(const MapCombinator&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename F>
MapCombinator<F>::MapCombinator(F user)
    : procedure_(std::move(user)) {}

template <typename F>
template <SomeFuture Input>
SomeFuture auto MapCombinator<F>::pipe(Input in) {
    return thunk::Map{std::move(in), std::move(procedure_)};
}

}  // namespace pipe

template <typename F>
auto Map(F proc) {
    return pipe::MapCombinator<F>{std::move(proc)};
}

}  // namespace renn::future
