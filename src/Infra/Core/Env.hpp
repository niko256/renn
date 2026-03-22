#pragma once


#include "IExecutor.hpp"
#include "State.hpp"
#include "Time/ITimerService.hpp"

namespace renn::rt {

using Env = State<
    IExecutor,
    time::ITimerService
    /* ... other services ... */
    >;

/* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

inline auto executor(const Env& state) -> IExecutor& {
    return state.get<IExecutor>();
}

inline auto timers(const Env& state) -> time::ITimerService& {
    return state.get<time::ITimerService>();
}

}  // namespace renn::rt
