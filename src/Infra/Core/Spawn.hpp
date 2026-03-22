#pragma once

#include "BoxedTask.hpp"
#include "Env.hpp"
#include "IExecutor.hpp"
#include "Task.hpp"
#include "Time/ITimerService.hpp"
#include "Time/Time.hpp"
#include "Time/TimerBase.hpp"

namespace renn {

/* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

/* Intrusive */
inline void submit(const rt::Env& where, TaskBase* what) {
    rt::executor(where).submit(what);
}

/* Fire and forget */
template <typename F>
void spawn(const rt::Env& where, F&& owned) {
    rt::executor(where).submit(new rt::BoxedTask(std::forward<F>(owned)));
}

/* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

/* backward-compatibility */
inline void submit(rt::IExecutor& where, TaskBase* what) {
    where.submit(what);
}

/* backward-compatibility */
template <typename F>
void spawn(rt::IExecutor& where, F&& owned) {
    where.submit(new rt::BoxedTask(std::forward<F>(owned)));
}

/* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

inline void set_timer(const rt::Env& where, time::Duration delay, time::TimerBase* what) {
    rt::timers(where).set(delay, what);
}

inline auto has_executor(const rt::Env& env) -> bool {
    return env.has<rt::IExecutor>();
}

inline auto has_timers(const rt::Env& env) -> bool {
    return env.has<time::ITimerService>();
}

}  // namespace renn
