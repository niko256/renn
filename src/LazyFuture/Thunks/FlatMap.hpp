#pragma once

#include "../Core/Role.hpp"
#include "../Core/Thunk.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Computation/Computation.hpp"
#include "../Continuation/Transform.hpp"
#include "../Continuation/Unwrap.hpp"
#include "../Trait/ValueOf.hpp"
#include <type_traits>

namespace renn::future::thunk {

template <Thunk Upstream, typename F>
class [[nodiscard]] FlatMap : public role::ThunkBase<FlatMap<Upstream, F>> {
  public:
    using InputType = trait::ValueOf<Upstream>;
    using InnerFuture = std::invoke_result_t<F, InputType>;
    using ValueType = trait::ValueOf<InnerFuture>;

    FlatMap(Upstream upstream, F func)
        : upstream_(std::move(upstream)),
          func_(std::move(func)) {}

    FlatMap(FlatMap&&) = default;

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream d) {
        auto unwrap = cont::Unwrap<InnerFuture, Downstream>{std::move(d)};

        auto transform
            = cont::Transform<InputType, InnerFuture, F, decltype(unwrap)>{
                std::move(func_), std::move(unwrap)
            };

        return upstream_.materialize(std::move(transform));
    }

  private:
    Upstream upstream_;
    F func_;
};

}  // namespace renn::future::thunk
