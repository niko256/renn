#pragma once

#include "../Core/Future.hpp"
#include "Map.hpp"
#include <tuple>
#include <utility>

namespace renn::future {

namespace pipe {

template <typename... Funcs>
struct [[nodiscard]] EveryCombinator {
    std::tuple<Funcs...> funcs_;

    explicit EveryCombinator(Funcs... fs)
        : funcs_(std::move(fs)...) {}

    EveryCombinator(EveryCombinator&&) = default;
    EveryCombinator(const EveryCombinator&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in) {
        return std::move(in)
               | Map([fs = std::move(funcs_)](auto value) mutable {
                     return apply_all(
                         value, fs, std::index_sequence_for<Funcs...>{}
                     );
                 });
    }

  private:
    /* Apply all functions to value and collect results in tuple */
    template <typename T, size_t... Is>
    static auto apply_all(
        const T& value,
        std::tuple<Funcs...>& funcs,
        std::index_sequence<Is...>
    ) {
        /* std::make_tuple(f0(value), f1(value), f2(value), ...) */
        return std::make_tuple(std::get<Is>(funcs)(value)...);
    }
};

}  // namespace pipe

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */


template <typename... Funcs>
auto Every(Funcs... funcs) {
    return pipe::EveryCombinator<Funcs...>{std::move(funcs)...};
}

}  // namespace renn::future
