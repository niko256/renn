#pragma once

#include "../../Runtime/Core/State.hpp"
#include "Computation.hpp"
#include <utility>

namespace renn::future::thunk {

namespace detail {

template <typename V> struct ContinuationArchetype {
    void proceed(V, rt::State){};
};

}  // namespace detail

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename T>
concept Thunk = requires {
    typename T::ValueType;

    {
        std::declval<T>().materialize(
            std::declval<
                detail::ContinuationArchetype<typename T::ValueType>>())

    } -> future::Computation;
};

}  // namespace renn::future::thunk
