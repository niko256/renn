#pragma once

#include "../Continuation/Continuation.hpp"
#include "../../Runtime/Core/Renn.hpp"
#include "../../Runtime/Core/State.hpp"
#include <algorithm>
#include <optional>

namespace renn::future::cont {

template <typename In, typename Out, typename F, typename Downstream>
struct Transform : role::ContinuationTag, public RennBase {
    using InputValue = In;
    using OutputValue = Out;

    F func_;
    Downstream downstream_;
    std::optional<In> input_;
    rt::State state_;

    Transform(F f, Downstream d);

    /* Pinned */
    Transform(Transform&&) = default;
    Transform(const Transform&) = delete;

    void proceed(In value, rt::State st);

    void run() noexcept override;
};

template <typename In, typename Out, typename F, typename Downstream>
Transform<In, Out, F, Downstream>::Transform(F f, Downstream d)
    : func_(std::move(f)),
      downstream_(std::move(d)),
      input_(std::nullopt),
      state_{} {}

template <typename In, typename Out, typename F, typename Downstream>
void Transform<In, Out, F, Downstream>::proceed(In value, rt::State st) {
    input_.emplace(std::move(value));
    state_ = st;

    rt::submit(state_.runtime, this);
}

template <typename In, typename Out, typename F, typename Downstream>
void Transform<In, Out, F, Downstream>::run() noexcept {
    downstream_.proceed(func_(std::move(*input_)), state_);
}


}  // namespace renn::future::cont
