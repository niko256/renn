#pragma once

#include "Map.hpp"
#include <tuple>
#include <utility>

namespace renn::future {

namespace pipe {

template <typename F>
struct [[nodiscard]] ThenCombinator {
    F func_;

    explicit ThenCombinator(F f)
        : func_(std::move(f)) {}

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in) {
        return std::move(in) | Map([f = std::move(func_)](auto tpl) mutable {
                   return std::apply(std::move(f), std::move(tpl));
               });
    }
};

}  // namespace pipe

template <typename F>
auto Then(F func) {
    return pipe::ThenCombinator<F>{std::move(func)};
}

}  // namespace renn::future
