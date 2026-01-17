#pragma once

#include "../Timerrrs/TSheduler.hpp"
#include "IExecutor.hpp"
#include "Renn.hpp"
#include <tuple>

namespace renn::rt {

using View = std::tuple<
    rt::IExecutor*,       /* [0] */
    timers::TScheduler*>; /* [1] */

/* ... */

inline IExecutor& executor(const View& v) {
    rt::IExecutor* exe = std::get<0>(v);
    assert(exe != nullptr && "Executor is not available...");
    return *exe;
}

inline timers::TScheduler& timers(const View& rt) {
    timers::TScheduler* timers = std::get<1>(rt);
    assert(timers != nullptr && "Timers are not available...");
    return *timers;
}

inline void submit(const View& rt, RennBase* renn) {
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


};  // namespace renn::rt
