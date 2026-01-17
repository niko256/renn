#pragma once

#include "../Runtime/State.hpp"

namespace renn::thunk {

template <typename C, typename V>
concept Continuation = requires(C cont, V v, rt::State s) {
    cont.continue(std::move(v), s);
}

};  // namespace renn::thunk
