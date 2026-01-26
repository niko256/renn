#pragma once

#include "Continuation.hpp"
#include "../../Runtime/Core/State.hpp"

namespace renn::future::cont {

template <typename V, typename Receiver>
struct Demand : role::ContinuationTag {
    using ValueType = V;

    Receiver* receiver_;

    explicit Demand(Receiver* r);

    Demand(Demand&&) = default;

    Demand(const Demand&) = delete;

    void proceed(V value, rt::State st);
};

template <typename V, typename Receiver>
Demand<V, Receiver>::Demand(Receiver* r)
    : receiver_(r) {}

template <typename V, typename Receiver>
void Demand<V, Receiver>::proceed(V value, rt::State /* st */) {
    receiver_->set(std::move(value));
}

}  // namespace renn::future::cont
