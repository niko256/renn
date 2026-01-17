#pragma once

namespace renn::thunk {

template <typename T>
concept Thunk = requires(T thunk, Demand<typename T::ValueType> dem) {
    typename T::ValueType;

    { thunk.materialize(dem) } -> future::Computation;
};

};  // namespace renn::thunk
