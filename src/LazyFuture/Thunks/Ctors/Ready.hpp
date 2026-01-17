#pragma once

#include "../../../Runtime/State.hpp"
#include "../../Core/Continuation.hpp"
#include <algorithm>

namespace renn::thunk {

template <typename V>
struct [[nodiscard]] Ready {
    V value_;

    explicit Ready(V v) : value_(std::move(v)) {}

    Ready(const Ready&) = delete;
    Ready& operator=(const Ready&) = delete;

    Ready(Ready&&) = default;

    using ValueType = V;

    template <Continuation<V> Consumer>
    struct Compute {
        V value_;
        Consumer cons_;

        void start(rt::View rt) {
            cons_.continue(std::move(value_), State{rt});
        }
    };

    template <Continuation<V> Consumer>
    future::Computation auto materialize(Consumer cons);
};

template <typename V, Continuation<V> Consumer>
future::Computation auto Ready<V>::materialize(Consumer cons) {
    return Compute<Consumer>{std::move(Ready::value_), std::move(cons)};
}

};  // namespace renn::thunk
