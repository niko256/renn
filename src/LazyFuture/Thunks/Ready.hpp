#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Computation.hpp"
#include "../Core/Continuation.hpp"
#include "../Trait/Linear.hpp"
#include <utility>

namespace renn::future::thunk {

template <typename V>
struct [[nodiscard]] Ready : support::AlmostLinear<Ready<V>> {
    using ValueType = V;

    ValueType value_;

    explicit Ready(V v);

    template <Continuation<V> Consumer>
    struct ComputeValue {
        ValueType value_;
        Consumer consumer_;

        void start(rt::View rt);
    };

    template <Continuation<V> Consumer>
    Computation auto materialize(Consumer cons);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename V>
Ready<V>::Ready(V v) : value_(std::move(v)) {}

template <typename V>
template <Continuation<V> Consumer>
void Ready<V>::ComputeValue<Consumer>::start(rt::View rt) {
    consumer_.proceed(std::move(value_), rt::State{rt});
}

template <typename V>
template <Continuation<V> Consumer>
Computation auto Ready<V>::materialize(Consumer cons) {
    return ComputeValue<Consumer>{std::move(value_), std::move(cons)};
}

}  // namespace renn::future::thunk
