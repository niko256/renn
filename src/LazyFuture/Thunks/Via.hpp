#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"

namespace renn::future::thunk {

template <Thunk Upstream>
class [[nodiscard]] Via : ThunkBase<Via<Upstream>> {
  public:
    using ValueType = trait::ValueOf<Upstream>;

    Via(Upstream pr, rt::View runtime);

    template <Continuation<ValueType> Downstream>
    struct MutateState {
        rt::View runtime_;
        Downstream consumer_;

        void proceed(ValueType v, rt::State st);
    };

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream c);

  private:
    Upstream upstream_;
    rt::View rt_;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-|
 */

template <Thunk Upstream>
Via<Upstream>::Via(Upstream pr, rt::View runtime)
    : upstream_(std::move(pr)),
      rt_(runtime) {}

template <Thunk Upstream>
template <Continuation<typename Via<Upstream>::ValueType> Downstream>
Via<Upstream>::MutateState<Downstream>::proceed(ValueType v, rt::State st) {
    consumer_.proceed(std::move(v), rt::State{rt_});
}

template <Thunk Upstream>
template <Continuation<typename Via<Upstream>::ValueType> Downstream>
Computation auto Via<Prod>::materialize(Downstream c) {
    return prod_.materialize(MutateState<Downstream>{rt_, std::move(c)});
}

}  // namespace renn::future::thunk
