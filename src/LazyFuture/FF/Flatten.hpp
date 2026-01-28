#pragma once

#include "../Core/Future.hpp"
#include "../Thunks/Flatten.hpp"

namespace renn::future {

namespace pipe {

struct [[nodiscard]] FlattenCombinator {
    template <SomeFuture Input>
    SomeFuture auto pipe(Input in) {
        return thunk::Flatten{std::move(in)};
    }
};

}  // namespace pipe

inline auto Flatten() {
    return pipe::FlattenCombinator{};
}


}  // namespace renn::future
