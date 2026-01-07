#include "Fiber.hpp"
#include "Coro.hpp"
#include "Handle.hpp"
#include "Syscalls.hpp"

namespace renn {

thread_local Fiber* Fiber::current_ = nullptr;

Fiber::Fiber(sched::IExecutor& sched, Routine routine)
    : coro_(std::move(routine)),
      sched_(sched),
      reason_(YieldTag{}) {}

void Fiber::schedule() {
    sched_.submit([this] {
        this->step();
    });
}

void Fiber::step() {
    auto prev_fiber = current_;
    current_ = this;

    coro_.resume();

    current_ = prev_fiber;


    /* polling the completion */
    if (coro_.is_done()) {
        /* std::cerr << "DEBUG: Fiber " << this << " Done." << std::endl; */
        delete this;
        return;
    }

    if (handler_) {
        auto handle = std::move(handler_);
        handle(FiberHandle(this));
    } else {
        /* ??? */
    }
}

void Fiber::suspend(Syscall reason, SuspendHandler sc_handler) {
    reason_ = reason;
    handler_ = std::move(sc_handler);
    coro_.suspend();
}

/* get current fiber */
Fiber* Fiber::current() {
    return current_;
}

void Fiber::set_current(Fiber* new_current) {
    current_ = new_current;
}

/* get internal coroutine */
Coroutine& Fiber::get_coro() {
    return coro_;
}

/* get internal scheduler */
sched::IExecutor& Fiber::current_scheduler() const {
    return sched_;
}
};  // namespace renn
