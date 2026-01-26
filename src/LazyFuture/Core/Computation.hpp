#pragma once

#include "../../Runtime/Core/View.hpp"

namespace renn::future {

/*
 * Materialized computation that represents a Pinned object
 */


template <typename C>
concept Computation = requires(C comp, rt::View rt) {
    { comp.start(rt) };
};

};  // namespace renn::future
