#pragma once

#include "../Computation/Computation.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Role.hpp"
#include "../Computation/Immediate.hpp"
#include <algorithm>
#include <utility>

namespace renn::future::thunk {

template <typename V>
class Ready final : public role::ThunkBase<Ready<V>> {
  private:
    /* +---+---+ */

    V value_;

    /* +---+---+ */
  public:
    using ValueType = V;

    /* +---+---+---+---+ */

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
