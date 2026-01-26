#pragma once

#include "../../Runtime/Core/View.hpp"

namespace renn::future {

/**
 * @PHILOSOPHY
 * Computation is like a compiled assembly - the abstract plan (Thunk)
 * has been compiled into concrete executable structure.
 */

template <typename C>
concept Computation = requires(C comp, rt::View rt) {
    { comp.start(rt) };
};

};  // namespace renn::future
