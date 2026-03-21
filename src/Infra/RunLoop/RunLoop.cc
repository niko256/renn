#include "RunLoop.hpp"
#include "Core/Env.hpp"
#include "Core/IExecutor.hpp"
#include "Core/State.hpp"
#include "Time/ITimerService.hpp"
#include <cstdlib>

namespace renn::rt {

auto RunLoop::env() -> Env {
    IExecutor& exe = *this;
    time::ITimerService& ts = *this;

    return Env::from(exe, this);
}

RunLoop::operator Env() {
    return env();
}

void RunLoop::submit(TaskBase* task) {
    {
        std::lock_guard lock(mtx_);
        tasks_.push_back(*task);
    }
    condvar_.notify_one();
}

void RunLoop::set(time::Duration delay, time::TimerBase* timer) {
    {
        std::lock_guard lock(mtx_);
        timer->deadline = std::chrono::steady_clock::now() + delay;
        timers_.add_timer(delay, timer);
    }
    condvar_.notify_one();
}

void RunLoop::run() {
    while (true) {
        TaskBase* task = nullptr;

        {
            std::unique_lock lock(mtx_);

            while (true) {
                timers_.move_expired_to(std::chrono::steady_clock::now(), tasks_);

                if (!tasks_.empty()) {
                    task = tasks_.try_pop_front();
                    break;
                }

                if (stop_requested_ && timers_.empty()) {
                    return;
                }

                auto next = timers_.next_deadline();
                if (next) {
                    condvar_.wait_until(lock, *next);
                } else if (stop_requested_) {
                    return;
                } else {
                    condvar_.wait(lock);
                }
            }
        }

        if (task) {
            try {
                task->run();
            } catch (...) {
                std::abort();
            }
        }
    }
}

void RunLoop::stop() {
    {
        std::lock_guard lock(mtx_);
        stop_requested_ = true;
    }
    condvar_.notify_all();
}

}  // namespace renn::rt
