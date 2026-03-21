#pragma once

#include "Continuation.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Trait/ComputationOf.hpp"
#include "Core/Env.hpp"
#include <optional>

namespace renn::future::cont {

template <typename InnerFuture, typename Downstream>
class Unwrap : public role::ContinuationTag {
  private:
    /* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

    using InnerValueType = trait::ValueOf<InnerFuture>;

    Downstream downstream_;

    struct Bridge : role::ContinuationTag {
        Unwrap* self_;

        Bridge(Unwrap* s)
            : self_(s) {}

        void proceed(InnerValueType value, rt::Env state) {
            self_->downstream_.proceed(std::move(value), state);
        }
    };

    using InnerComp = trait::ComputationOf<InnerFuture, Bridge>;
    std::optional<InnerComp> inner_comp_;

    /* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

  public:
    Unwrap(Downstream d)
        : downstream_(std::move(d)),
          inner_comp_(std::nullopt) {}

    void proceed(InnerFuture inner, rt::Env state) {
        inner_comp_.emplace(std::move(inner).materialize(Bridge{this}));

        inner_comp_->start(state.rt());
    }
};

}  // namespace renn::future::cont
