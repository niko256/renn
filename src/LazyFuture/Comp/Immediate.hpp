#pragma once

#include "../Core/Role.hpp"
#include "../Core/Continuation.hpp"
#include "../../Runtime/Core/View.hpp"
#include "../../Runtime/Core/State.hpp"

namespace renn::future::comp {

/**
 * @brief Materialized computation
 */
template <typename V, typename Downstream>
struct Immediate : role::ComputationBase<Immediate<V, Downstream>> {
    using ValueType = V;

    V value_;
    Downstream downstream_;

    Immediate(V v, Downstream d);

    Immediate(Immediate&&) = default;

    Immediate(const Immediate&) = delete;

    void start(rt::View rt);
};

template <typename V, typename Downstream>
Immediate<V, Downstream>::Immediate(V v, Downstream d)
    : value_(std::move(v)),
      downstream_(std::move(d)) {}

template <typename V, typename Downstream>
void Immediate<V, Downstream>::start(rt::View rt) {
    downstream_.proceed(std::move(value_), rt::State{rt});
}

}  // namespace renn::future::comp
