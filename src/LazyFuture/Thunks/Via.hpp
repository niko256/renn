#pragma once

#include "../../Infra/Core/Env.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Continuation/MutateState.hpp"
#include "LazyFuture/Core/Role.hpp"

namespace renn::future::thunk {

template <Thunk Upstream>
class Via final : public role::ThunkBase<Via<Upstream>> {
  private:
    /* +---+---+---+---+ */

    Upstream upstream_;
    rt::Env rt_;

    /* +---+---+---+---+ */

  public:
    using ValueType = trait::ValueOf<Upstream>;

    /* +---+---+---+---+---+---+---+---+---+---+ */

    Via(Via&&) = default;

    Via(Upstream pr, rt::Env runtime)
        : upstream_(std::move(pr)),
          rt_(runtime) {}

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream c) {
        auto mutator = cont::MutateState<ValueType, Downstream>{rt_, std::move(c)};

        return upstream_.materialize(std::move(mutator));
    }
};

}  // namespace renn::future::thunk
