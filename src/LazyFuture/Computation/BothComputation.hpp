#pragma once

#include "../Core/Role.hpp"
#include "Computation.hpp"
#include "../Continuation/BothReceiver.hpp"
#include "../Trait/ComputationOf.hpp"
#include "../../Runtime/Core/View.hpp"
#include <memory>

namespace renn::future::comp {

/* BothComputation — starts two computations in parallel */
template <typename LeftFuture, typename RightFuture, typename Downstream>
class Both : role::ComputationBase<Both<LeftFuture, RightFuture, Downstream>> {
  private:
    using L = trait::ValueOf<LeftFuture>;
    using R = trait::ValueOf<RightFuture>;
    using Consumer = cont::BothReceiver<L, R, Downstream>;

    using LeftComp = trait::ComputationOf<LeftFuture, typename Consumer::LeftCont>;
    using RightComp = trait::ComputationOf<RightFuture, typename Consumer::RightCont>;

    std::unique_ptr<Consumer> consumer_;

    LeftComp leftComp_;
    RightComp rightComp_;

  public:
    Both(LeftFuture left, RightFuture right, Downstream downstream)
        : consumer_(std::make_unique<Consumer>(std::move(downstream))),
          leftComp_(std::move(left).materialize(typename Consumer::LeftCont{consumer_.get()})),
          rightComp_(
              std::move(right).materialize(typename Consumer::RightCont{consumer_.get()})
          ) {}

    void start(rt::View rt) {
        leftComp_.start(rt);
        rightComp_.start(rt);
    }
};

}  // namespace renn::future::comp
