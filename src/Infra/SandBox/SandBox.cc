#include "SandBox.hpp"
#include "Core/Env.hpp"
#include "Core/IExecutor.hpp"
#include "Core/Task.hpp"
#include "Time/ITimerService.hpp"
#include "Time/Time.hpp"
#include "Time/TimerBase.hpp"

namespace renn::rt {

/* @todo ... */

auto SandBox::env() -> Env {
    IExecutor& exe = *this;
    time::ITimerService& ts = *this;

    return Env::from(exe, ts);
}

SandBox::operator Env() {
    return env();
}

void SandBox::submit(TaskBase* task) {
    tasks_.push_back(*task);
}

void SandBox::set(time::Duration delay, time::TimerBase* timer) {
    auto point = clock_.now() + delay;
    timer->deadline = point;

    timers_.add_timer(point, timer);
}

}  // namespace renn::rt
