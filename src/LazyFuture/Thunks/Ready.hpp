#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Computation/Computation.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Role.hpp"
#include "../Computation/Immediate.hpp"
#include <algorithm>
#include <utility>

namespace renn::future::thunk {

template <typename ValueType>
class Ready final : public role::ThunkBase<Ready<V>> {
  private:
    ValueType value_;

  public:
    explicit Ready(ValueType v)
        : value_(std::move(v)) {}

    Ready(Ready&&) = default;
    Ready& operator=(Ready&&) = default;

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream cons) {
        return comp::Immediate<ValueType, Downstream>{std::move(value_), std::move(cons)};
    }
};


}  // namespace renn::future::thunk
