#pragma once

#include "View.hpp"

namespace renn::rt {

struct State {
    View runtime;

    /* ... */


    inline auto rt() -> View {
        return runtime;
    }
};

}  // namespace renn::rt
