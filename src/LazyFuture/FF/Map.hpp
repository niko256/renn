#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Map.hpp"
#include <utility>

namespace renn::future {

namespace pipe {

template <typename F>
struct [[nodiscard]] MapAdapter {
    F procedure_;

    explicit MapAdapter(F user);

    MapAdapter(const MapAdapter&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename F>
MapAdapter<F>::MapAdapter(F user) : procedure_(std::move(user)) {}

template <typename F>
template <SomeFuture Input>
SomeFuture auto MapAdapter<F>::pipe(Input in) {
    return thunk::Map{std::move(in), std::move(procedure_)};
}

}  // namespace pipe

template <typename F>
auto Map(F proc) {
    return pipe::MapAdapter<F>{std::move(proc)};
}

}  // namespace renn::future
