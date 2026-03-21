#pragma once

#include "../Core/Role.hpp"
#include "../Core/Thunk.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Computation/Computation.hpp"
#include "../Computation/BothComputation.hpp"
#include "../Trait/ValueOf.hpp"
#include <tuple>

namespace renn::future::thunk {

/* Both — runs two futures in parallel, returns pair of results */
template <Thunk Left, Thunk Right>
class Both final : public role::ThunkBase<Both<Left, Right>> {
  private:
    Left left_;
    Right right_;

  public:
    using LeftValue = trait::ValueOf<Left>;
    using RightValue = trait::ValueOf<Right>;
    using ValueType = std::tuple<LeftValue, RightValue>;

    Both(Left left, Right right)
        : left_(std::move(left)),
          right_(std::move(right)) {}

    Both(Both&&) = default;

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream d) {
        return comp::Both<Left, Right, Downstream>{
            std::move(left_), std::move(right_), std::move(d)
        };
    }
};

}  // namespace renn::future::thunk
