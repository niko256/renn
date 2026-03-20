#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Computation/Computation.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Role.hpp"
#include "../Computation/Immediate.hpp"
#include <algorithm>
#include <utility>

namespace renn::future::thunk {

template <typename V>
class [[nodiscard]] Ready : public role::ThunkBase<Ready<V>> {
  public:
    using ValueType = V;

    explicit Ready(V v)
        : value_(std::move(v)) {}

    Ready(Ready&&) = default;
    Ready& operator=(Ready&&) = default;

    template <Continuation<V> Downstream>
    Computation auto materialize(Downstream cons) {
        return comp::Immediate<V, Downstream>{
            std::move(value_), std::move(cons)
        };
    }

  private:
    ValueType value_;
};


}  // namespace renn::future::thunk
