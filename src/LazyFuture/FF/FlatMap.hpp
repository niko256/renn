#pragma once

#include <utility>
#include "../Core/Future.hpp"
#include "../Thunks/FlatMap.hpp"

namespace renn::future {

namespace pipe {

template <typename F>
struct [[nodiscard]] FlatMapCombinator {
    F func_;

    FlatMapCombinator(F f)
        : func_(std::move(f)) {}

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in) {
        return thunk::FlatMap{std::move(in), std::move(func_)};
    }
};

}  // namespace pipe

template <typename F>
auto FlatMap(F func) {
    return pipe::FlatMapCombinator<F>{std::move(func)};
}

}  // namespace renn::future
