#include "MtRuntime.hpp"
#include "Core/Env.hpp"
#include "Core/IExecutor.hpp"
#include "Core/State.hpp"
#include "Infra/Time/ITimerService.hpp"

namespace renn::rt {

Runtime::Runtime(size_t num_workers)
    : thread_pool_(num_workers) {}

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

Runtime::operator Env() {
    auto e = Env::from<IExecutor>(thread_pool_);

    if (timer_thread_.has_value()) {
        e = e.with<time::ITimerService>(*timer_thread_);
    }

    return e;
}

bool Runtime::here() const {
    return exe::ThreadPool::current() == &thread_pool_;
}

}  // namespace renn::rt
