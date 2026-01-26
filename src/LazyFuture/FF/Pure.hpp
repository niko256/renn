#pragma once

#include "../Core/Unit.hpp"
#include "../Core/Future.hpp"
#include "../Thunks/Pure.hpp"

namespace renn::future {

inline Future<Unit> auto Pure() {
    return thunk::Pure{};
}

}  // namespace renn::future
