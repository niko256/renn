#include "MtRuntime.hpp"

namespace renn::multi_thread {

Runtime::Runtime(size_t num_workers)
    : thread_pool_(num_workers) {
}

Runtime& Runtime::with_timers() {
    if (!timer_thread_.has_value()) {
        timer_thread_.emplace(&thread_pool_);
    }
    return *this;
}

void Runtime::start() {
    thread_pool_.start();

    if (timer_thread_.has_value()) {
        timer_thread_->start();
    }
}

void Runtime::stop() {
    if (timer_thread_.has_value()) {
        timer_thread_->stop();
    }

    thread_pool_.stop();
}

Runtime::operator View() {
    timer::IScheduler* ts = nullptr;

    if (timer_thread_.has_value()) {
        ts = &(*timer_thread_);
    }

    return {&thread_pool_, ts};
}

bool Runtime::here() const {
    return ThreadPool::current() == &thread_pool_;
}

} /* namespace renn::multi_thread */
