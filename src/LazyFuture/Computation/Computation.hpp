#pragma once

#include "../../Infra/Core/Env.hpp"

namespace renn::future {

/**
 * @PHILOSOPHY
 * Computation is like a compiled assembly - the abstract plan (Thunk)
 * has been compiled into concrete structure
 * that _pinned_ in memory and ready to be executed.
 */

template <typename C>
concept Computation = requires(C comp, rt::Env rt) {
    { comp.start(rt) };
};

};  // namespace renn::future
