#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/Linear.hpp"
#include "../Trait/ValueOf.hpp"

namespace renn::future::thunk {

template <Thunk Prod>
class [[nodiscard]] Via : support::AlmostLinear<Via<Prod>> {
  public:
    using ValueType = trait::ValueOf<Prod>;

    Via(Prod pr, rt::View runtime);

    template <Continuation<ValueType> Cons>
    struct MutateState {
        rt::View runtime_;
        Cons consumer_;

        void proceed(ValueType v, rt::State st);
    };

    template <Continuation<ValueType> Cons>
    Computation auto materialize(Cons c);

  private:
    Prod prod_;
    rt::View rt_;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <Thunk Prod>
Via<Prod>::Via(Prod pr, rt::View runtime) : prod_(std::move(pr)), rt_(runtime) {}

template <Thunk Prod>
template <Continuation<typename Via<Prod>::ValueType> Cons>
Via<Prod>::MutateState<Cons>::proceed(ValueType v, rt::State st) {
    consumer_.proceed(std::move(v), rt::State{rt_});
}

template <Thunk Prod>
template <Continuation<typename Via<Prod>::ValueType> Cons>
Computation auto Via<Prod>::materialize(Cons c) {
    return prod_.materialize(MutateState<Cons>{rt_, std::move(c)});
}

}  // namespace renn::future::thunk
