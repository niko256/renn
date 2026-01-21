#include "TimerThread.hpp"

namespace renn::timers {

TimerThread::TimerThread(rt::IExecutor* executor)
    : executor_(executor) {
}

void TimerThread::set(Duration delay, TimerBase* timer) {
    {
        std::lock_guard lock(mtx_);
        timer->deadline = SystemClock::now() + delay;
        timers_.add(timer);
    }
    cv_.notify_one();
}

void TimerThread::start() {
    thread_ = std::thread([this] {
        run_loop();
    });
}

void TimerThread::stop() {
    {
        std::lock_guard lock(mtx_);
        stopped_ = true;
    }
    cv_.notify_all();

    if (thread_.joinable()) {
        thread_.join();
    }
}

void TimerThread::run_loop() {
    /*
     *
     */
}

}  // namespace renn::timers
