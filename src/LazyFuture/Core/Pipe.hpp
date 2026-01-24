#pragma once

#include "Future.hpp"
#include <utility>

namespace renn {

template <future::SomeFuture F, typename Combinator>
auto operator|(F f, Combinator comb) {
    return comb.pipe(std::move(f));
}

}  // namespace renn
