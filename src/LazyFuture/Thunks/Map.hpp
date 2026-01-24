#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../Core/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include <optional>
#include <type_traits>

namespace renn::future::thunk {

/*
 * | Future<T> -> (T -> U) -> Future<U> |
 */
template <Thunk Upstream, typename F>
struct [[nodiscard]] Map : role::ThunkBase<Map<Upstream, F>> {
    using InputType = trait::ValueOf<Upstream>;
    using OutputType = std::invoke_result_t<F, InputType>;

    using ValueType = OutputType;

    Upstream producer_;
    F procedure_;

    Map(Upstream pr, F user);

    template <Continuation<OutputType> Downstream>
    struct MapTask : public RennBase {
        F user_;
        Downstream consumer_;
        std::optional<InputType> input_;
        rt::State state_;

        MapTask(F u, Downstream c);

        void proceed(InputType value, rt::State st);

        void run() noexcept override;
    };

    template <Continuation<OutputType> Downstream>
    Computation auto materialize(Downstream cons);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <Thunk Upstream, typename F>
Map<Upstream, F>::Map(Upstream pr, F user)
    : producer_(std::move(pr)),
      procedure_(std::move(user)) {}

template <Thunk Upstream, typename F>
template <Continuation<typename Map<Upstream, F>::OutputType> Downstream>
Map<Upstream, F>::MapTask<Downstream>::MapTask(F u, Downstream c)
    : user_(std::move(u)),
      consumer_(std::move(c)),
      input_(std::nullopt),
      state_{} {}

template <Thunk Upstream, typename F>
template <Continuation<typename Map<Upstream, F>::OutputType> Downstream>
void Map<Upstream, F>::MapTask<Downstream>::proceed(
    typename Map<Upstream, F>::InputType value, rt::State st
) {
    input_.emplace(std::move(value));
    state_ = st;

    rt::submit(state_.runtime, this);
}

template <Thunk Upstream, typename F>
template <Continuation<typename Map<Upstream, F>::OutputType> Downstream>
void Map<Upstream, F>::MapTask<Downstream>::run() noexcept {
    consumer_.proceed(user_(std::move(*input_)), state_);
}

template <Thunk Upstream, typename F>
template <Continuation<typename Map<Upstream, F>::OutputType> Downstream>
Computation auto Map<Upstream, F>::materialize(Downstream cons) {
    return producer_.materialize(
        MapTask<Downstream>{std::move(procedure_), std::move(cons)}
    );
}

}  // namespace renn::future::thunk
