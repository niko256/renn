#pragma once


#include "IExecutor.hpp"
#include "State.hpp"
#include "Time/IClock.hpp"
#include "Time/ITimerService.hpp"

namespace renn::rt {

using Env = State<
    IExecutor,
    time::ITimerService,
    time::IClock
    /* ... other services ... */
    >;

/* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

inline auto executor(const Env& state) -> IExecutor& {
    return state.get<IExecutor>();
}

inline auto timers(const Env& state) -> time::ITimerService& {
    return state.get<time::ITimerService>();
}

inline auto clock(const Env& state) -> time::IClock& {
    return state.get<time::IClock>();
}

}  // namespace renn::rt
