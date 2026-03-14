#pragma once

#include "../Timerrrs/TScheduler.hpp"
#include "IExecutor.hpp"
#include "Task.hpp"
#include <tuple>

namespace renn::rt {

using View = std::tuple<
    rt::IExecutor*,       /* [0] */
    timers::TScheduler*>; /* [1] */

/* ... */

inline auto executor(const View& v) -> IExecutor& {
    rt::IExecutor* exe = std::get<0>(v);
    assert(exe != nullptr && "Executor is not available...");
    return *exe;
}

inline auto timers(const View& rt) -> timers::TScheduler& {
    timers::TScheduler* timers = std::get<1>(rt);
    assert(timers != nullptr && "Timers are not available...");
    return *timers;
}

inline void submit(const View& rt, TaskBase* renn) {
    executor(rt).submit(renn);
}

inline void set_timer(const View& rt, timers::Duration delay, timers::TimerBase* timer) {
    timers(rt).set(delay, timer);
}

inline bool has_executor(const View& v) {
    return std::get<0>(v) != nullptr;
}

inline bool has_timers(const View& v) {
    return std::get<1>(v) != nullptr;
}

inline View make_view(IExecutor& exe) {
    return View{&exe, nullptr};
}

inline auto make_view(IExecutor& exe, timers::TScheduler& sched) -> View {
    return View{&exe, &sched};
}

}  // namespace renn::rt
