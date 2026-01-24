#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Computation.hpp"
#include "../Core/Continuation.hpp"
#include "../Core/Role.hpp"
#include <utility>

namespace renn::future::thunk {

template <typename V>
struct [[nodiscard]] Ready : role::ThunkBase<Ready<V>> {
    using ValueType = V;

    ValueType value_;

    explicit Ready(V v)
        : value_(std::move(v)) {}

    Ready(Ready&&) = default;
    Ready& operator=(Ready&&) = default;

    template <Continuation<V> Downstream>
    struct ComputeValue : role::ComputationBase<ComputeValue<Downstream>> {
        ValueType value_;
        Downstream consumer_;

        ComputeValue(ValueType v, Downstream c)
            : value_(std::move(v)),
              consumer_(std::move(c)) {};

        void start(rt::View rt);
    };

    template <Continuation<V> Downstream>
    Computation auto materialize(Downstream cons);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename V>
template <Continuation<V> Downstream>
void Ready<V>::ComputeValue<Downstream>::start(rt::View rt) {
    consumer_.proceed(std::move(value_), rt::State{rt});
}

template <typename V>
template <Continuation<V> Downstream>
Computation auto Ready<V>::materialize(Downstream cons) {
    return ComputeValue<Downstream>{std::move(value_), std::move(cons)};
}

}  // namespace renn::future::thunk
