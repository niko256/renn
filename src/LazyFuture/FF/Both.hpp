#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Both.hpp"

namespace renn::future {

template <SomeFuture Left, SomeFuture Right>
SomeFuture auto Both(Left left, Right right) {
    return thunk::Both{std::move(left), std::move(right)};
}

}  // namespace renn::future
