#include "TimerThread.hpp"
#include <vector>

namespace renn::timers {

TimerThread::TimerThread(rt::IExecutor* executor)
    : executor_(executor) {
}

void TimerThread::set(Duration delay, TimerBase* timer) {
    Timepoint deadline = Clock::now() + delay;
    timers_.push(deadline, timer);
}

void TimerThread::start() {
    thread_ = std::thread([this] {
        run_loop();
    });
}

void TimerThread::stop() {
    timers_.close();

    if (thread_.joinable()) {
        thread_.join();
    }
}

void TimerThread::run_loop() {
    std::vector<timer::TimerBase*> ready;
    ready.reserve(32);

    while (true) {
        ready.clear();

        if (!timers_.pop_ready_blocking(ready)) {
            break;
        }

        for (timer::TimerBase* timer : ready) {
            executor_->submit(timer);
        }
    }
}

}  // namespace renn::timers
