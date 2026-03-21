#pragma once

#include "../../Infra/Core/Env.hpp"
#include "../Core/Future.hpp"
#include "../Thunks/Via.hpp"

namespace renn::future {

namespace pipe {

class ViaCombinator {
  private:
    rt::Env state_;

  public:
    explicit ViaCombinator(rt::Env rt);

    ViaCombinator(const ViaCombinator&) = delete;

    template <SomeFuture Input>
    SomeFuture auto pipe(Input in);
};

/* +---+---+---+---+---+---+---+---+---+---+---+---+ */

ViaCombinator::ViaCombinator(rt::Env rt)
    : state_(rt) {}

template <SomeFuture Input>
SomeFuture auto ViaCombinator::pipe(Input in) {
    return thunk::Via{std::move(in), state_};
}

}  // namespace pipe

inline auto Via(rt::Env runtime) {
    return pipe::ViaCombinator{runtime};
}

}  // namespace renn::future
