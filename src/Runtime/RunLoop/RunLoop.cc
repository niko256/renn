#include "RunLoop.hpp"
#include <cstdlib>

namespace renn::rt {

Runtime::operator View() {
    return {this, this};
}

void Runtime::submit(RennBase* renn) {
    {
        std::lock_guard lock(mtx_);
        renns_.PushBack(renn);
    }
    condvar_.notify_one();
}

void Runtime::set(timers::Duration delay, timers::TimerBase* timer) {
    {
        std::lock_guard lock(mtx_);
        timer->deadline = std::chrono::steady_clock::now() + delay;
        timers_.add(timer);
    }
    condvar_.notify_one();
}

void Runtime::run() {
    while (true) {
        RennBase* renn = nullptr;

        {
            std::unique_lock lock(mtx_);

            while (true) {
                // 1. Move expired timers
                timers_.move_expired_to(std::chrono::steady_clock::now(), renns_);

                // 2. Check tasks
                if (!renns_.IsEmpty()) {
                    renn = renns_.PopFront();
                    break;
                }

                // 3. Check stop
                if (stop_requested_ && timers_.empty()) {
                    return;
                }

                // 4. Wait
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

        if (renn) {
            try {
                renn->run();
            } catch (...) {
                std::abort();
            }
        }
    }
}

void Runtime::stop() {
    {
        std::lock_guard lock(mtx_);
        stop_requested_ = true;
    }
    condvar_.notify_all();
}

}  // namespace renn::rt
