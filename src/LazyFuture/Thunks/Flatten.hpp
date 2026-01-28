#pragma once

#include "../Core/Role.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Continuation/Unwrap.hpp"

namespace renn::future::thunk {

template <Thunk Upstream>
class [[nodiscard]] Flatten : public role::ThunkBase<Flatten<Upstream>> {
  public:
    using InnerFuture = trait::ValueOf<Upstream>;
    using ValueType = trait::ValueOf<InnerFuture>;

    Upstream upstream_;

    Flatten(Upstream upstream)
        : upstream_(std::move(upstream)) {}

    Flatten(Flatten&&) = default;
    Flatten& operator=(Flatten&&) = default;

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream d) {
        auto unwrap = cont::Unwrap<InnerFuture, Downstream>{std::move(d)};

        return upstream_.materialize(std::move(unwrap));
    }
};

}  // namespace renn::future::thunk
