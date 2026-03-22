#include "TimerThread.hpp"
#include "Time/Time.hpp"

namespace renn::time {

TimerThread::TimerThread(rt::IExecutor* executor)
    : executor_(executor) {}

void TimerThread::set(Duration delay, TimerBase* timer) {
    {
        std::lock_guard lock(mtx_);
        auto point = SystemClock::now() + delay;

        timer->deadline = point;
        timers_.add_timer(point, timer);
    }
    cv_.notify_one();
}

void TimerThread::start() {
    thread_ = std::thread([this] { run_loop(); });
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

}  // namespace renn::time
