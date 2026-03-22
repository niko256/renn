#pragma once

#include "../Continuation/Continuation.hpp"
#include "../../Infra/Core/Task.hpp"
#include "Core/Env.hpp"
#include "Core/Spawn.hpp"
#include <algorithm>
#include <optional>

namespace renn::future::cont {

template <typename In, typename Out, typename F, typename Downstream>
class Transform : public role::ContinuationTag, public TaskBase {
  private:
    /* +---+---+---+---+---+ */

    F func_;
    Downstream downstream_;
    std::optional<In> input_;
    rt::Env state_;

    /* +---+---+---+---+---+ */

  public:
    using InputValue = In;
    using OutputValue = Out;

    /* +---+---+---+---+---+---+---+ */

  public:
    Transform(F f, Downstream d);

    /* Pinned */
    Transform(Transform&&) = default;
    Transform(const Transform&) = delete;

    void proceed(In value, rt::Env st);

    void run() noexcept override;
};

template <typename In, typename Out, typename F, typename Downstream>
Transform<In, Out, F, Downstream>::Transform(F f, Downstream d)
    : func_(std::move(f)),
      downstream_(std::move(d)),
      input_(std::nullopt),
      state_{} {}

template <typename In, typename Out, typename F, typename Downstream>
void Transform<In, Out, F, Downstream>::proceed(In value, rt::Env st) {
    input_.emplace(std::move(value));
    state_ = st;

    renn::submit(state_, this);
}

template <typename In, typename Out, typename F, typename Downstream>
void Transform<In, Out, F, Downstream>::run() noexcept {
    downstream_.proceed(func_(std::move(*input_)), state_);
}


}  // namespace renn::future::cont
