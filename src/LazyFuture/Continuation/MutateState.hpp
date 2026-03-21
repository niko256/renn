#pragma once

#include "Continuation.hpp"
#include "../../Infra/Core/Env.hpp"

namespace renn::future::cont {

template <typename V, typename Downstream>
struct MutateState : role::ContinuationTag {
    using ValueType = V;

    rt::Env target_;
    Downstream downstream_;

    MutateState(rt::Env rt, Downstream d);

    MutateState(MutateState&&) = default;

    MutateState(const MutateState&) = delete;

    void proceed(V value, rt::Env state);
};

template <typename V, typename Downstream>
MutateState<V, Downstream>::MutateState(rt::Env rt, Downstream d)
    : target_(rt),
      downstream_(std::move(d)) {}

template <typename V, typename Downstream>
void MutateState<V, Downstream>::proceed(V value, rt::Env /* state */) {
    downstream_.proceed(std::move(value), rt::Env{target_});
}


}  // namespace renn::future::cont
