#pragma once

#include "../../Runtime/Core/View.hpp"
#include "../Core/Future.hpp"
#include "../Thunks/Via.hpp"

namespace renn::future {

namespace pipe {

struct [[nodiscard]] Via {
    rt::View runtime_;

    explicit Via(rt::View rt);

    Via(const Via&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

Via::Via(rt::View rt) : runtime_(rt) {}

template <SomeFuture Input>
SomeFuture auto Via::pipe(Input in) {
    return thunk::Via{std::move(in), runtime_};
}

}  // namespace pipe

inline auto Via(rt::View runtime) {
    return pipe::Via{runtime};
}

}  // namespace renn::future
