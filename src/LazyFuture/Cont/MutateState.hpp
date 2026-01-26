#pragma once

#include "../Core/Continuation.hpp"
#include "../../Runtime/Core/View.hpp"
#include "../../Runtime/Core/State.hpp"

namespace renn::future::cont {

template <typename V, typename Downstream>
struct MutateState : role::ContinuationTag {
    using ValueType = V;

    rt::View target_;
    Downstream downstream_;

    MutateState(rt::View rt, Downstream d);

    MutateState(MutateState&&) = default;

    MutateState(const MutateState&) = delete;

    void proceed(V value, rt::State state);
};

template <typename V, typename Downstream>
MutateState<V, Downstream>::MutateState(rt::View rt, Downstream d)
    : target_(rt),
      downstream_(std::move(d)) {}

template <typename V, typename Downstream>
void MutateState<V, Downstream>::proceed(V value, rt::State /* state */) {
    downstream_.proceed(std::move(value), rt::State{target_});
}


}  // namespace renn::future::cont
