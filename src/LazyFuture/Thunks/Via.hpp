#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Continuation/MutateState.hpp"

namespace renn::future::thunk {

template <Thunk Upstream>
class [[nodiscard]] Via : public role::ThunkBase<Via<Upstream>> {
  public:
    using ValueType = trait::ValueOf<Upstream>;

    Via(Via&&) = default;

    Via(Upstream pr, rt::View runtime)
        : upstream_(std::move(pr)),
          rt_(runtime) {}

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream c) {
        auto mutator
            = cont::MutateState<ValueType, Downstream>{rt_, std::move(c)};

        return upstream_.materialize(std::move(mutator));
    }

  private:
    Upstream upstream_;
    rt::View rt_;
};

}  // namespace renn::future::thunk
