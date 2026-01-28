#pragma once

#include "Continuation.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Trait/ComputationOf.hpp"
#include <optional>

namespace renn::future::cont {

template <typename InnerFuture, typename Downstream>
struct Unwrap : public role::ContinuationTag {
    using InnerValueType = trait::ValueOf<InnerFuture>;

    Downstream downstream_;

    struct Bridge : role::ContinuationTag {
        Unwrap* self_;

        Bridge(Unwrap* s)
            : self_(s) {}

        void proceed(InnerValueType value, rt::State state) {
            self_->downstream_.proceed(std::move(value), state);
        }
    };

    using InnerComp = trait::ComputationOf<InnerFuture, Bridge>;
    std::optional<InnerComp> inner_comp_;

    Unwrap(Downstream d)
        : downstream_(std::move(d)),
          inner_comp_(std::nullopt) {}

    void proceed(InnerFuture inner, rt::State state) {
        inner_comp_.emplace(std::move(inner).materialize(Bridge{this}));

        inner_comp_->start(state.rt());
    }
};

}  // namespace renn::future::cont
