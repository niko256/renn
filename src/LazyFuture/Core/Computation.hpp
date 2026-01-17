#pragma once

#include "../Runtime/State.hpp"

namespace renn::future {

template <typename C>
concept Computation = requires(C comp, rt::View rt) {
    comp.start(rt);
};

};  // namespace renn::future
