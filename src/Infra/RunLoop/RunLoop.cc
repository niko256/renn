#include "RunLoop.hpp"
#include "Core/Env.hpp"
#include "Core/IExecutor.hpp"
#include "Time/ITimerService.hpp"
#include <chrono>
#include <cstdlib>

namespace renn::rt {

auto RunLoop::env() -> Env {
    IExecutor& exe = *this;
    time::ITimerService& ts = *this;

    return Env::from(exe, ts);
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
        timers_.add_timer(timer->deadline, timer);
    }
    condvar_.notify_one();
}

void RunLoop::run() {
    while (true) {
        TaskBase* task = nullptr;

        {
            std::unique_lock lock(mtx_);

            while (true) {
                auto expired = timers_.extract_expired(std::chrono::steady_clock::now());

                while (not expired.empty()) {
                    tasks_.push_back(expired.front());
                    expired.pop_front();
                }

                if (not tasks_.empty()) {
                    task = tasks_.try_pop_front();

                    break;
                }

                if (stop_requested_ and timers_.empty()) {
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
