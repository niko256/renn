#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../Core/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/Linear.hpp"
#include "../Trait/ValueOf.hpp"
#include <optional>
#include <type_traits>

namespace renn::future::thunk {

template <Thunk Prod, typename F>
struct [[nodiscard]] Map : support::AlmostLinear<Map<Prod, F>> {
    using InputType = trait::ValueOf<Prod>;
    using OutputType = std::invoke_result_t<F, InputType>;

    using ValueType = OutputType;

    Prod prod_;
    F procedure_;

    Map(Prod pr, F user);

    template <Continuation<OutputType> Cons>
    struct MapTask : public RennBase {
        F user_;
        Cons consumer_;
        std::optional<InputType> input_;
        rt::State state_;

        MapTask(F u, Cons c);

        void proceed(InputType v, rt::State st);

        void run() noexcept override;
    };

    template <Continuation<OutputType> Cons>
    Computation auto materialize(Cons cons);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <Thunk Prod, typename F>
Map<Prod, F>::Map(Prod pr, F user) : prod_(std::move(pr)), procedure_(std::move(user)) {}

template <Thunk Prod, typename F>
template <Continuation<typename Map<Prod, F>::OutputType> Cons>
Map<Prod, F>::MapTask<Cons>::MapTask(F u, Cons c) : user_(std::move(u)),
                                                    consumer_(std::move(c)),
                                                    input_(std::nullopt),
                                                    state_{} {}

template <Thunk Prod, typename F>
template <Continuation<typename Map<Prod, F>::OutputType> Cons>
Map<Prod, F>::MapTask<Cons>::proceed(InputType v, rt::State st) {
    input_.emplace(std::move(v));
    state_ = st;

    rt::submit(state_.runtime, this);
}

template <Thunk Prod, typename F>
template <Continuation<typename Map<Prod, F>::OutputType> Cons>
void Map<Prod, F>::MapTask<Cons>::run() noexcept {
    consumer_.proceed(user_(std::move(*input_)), state_);
}

template <Thunk Prod, typename F>
template <Continuation<typename Map<Prod, F>::OutputType> Cons>
Computation auto Map<Prod, F>::materialize(Cons cons) {
    return prod_.materialize(MapTask<Cons>{std::move(procedure_), std::move(cons)});
}

}  // namespace renn::future::thunk
