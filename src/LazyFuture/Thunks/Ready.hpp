#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Computation/Computation.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Role.hpp"
#include "../Computation/Immediate.hpp"
#include <algorithm>
#include <utility>

namespace renn::future::thunk {

template <typename V>
struct [[nodiscard]] Ready : public role::ThunkBase<Ready<V>> {
    using ValueType = V;

    ValueType value_;

    explicit Ready(V v);

    Ready(Ready&&) = default;
    Ready& operator=(Ready&&) = default;

    template <Continuation<V> Downstream>
    Computation auto materialize(Downstream cons);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename V>
Ready<V>::Ready(V v)
    : value_(std::move(v)) {}

template <typename V>
template <Continuation<V> Downstream>
Computation auto Ready<V>::materialize(Downstream cons) {
    return comp::Immediate<V, Downstream>{std::move(value_), std::move(cons)};
}

}  // namespace renn::future::thunk
