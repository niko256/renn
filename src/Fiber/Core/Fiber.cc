#include "Fiber.hpp"
#include "../../Utils/Assert.hpp"
#include "Awaiter.hpp"
#include "Coro.hpp"
#include "Handle.hpp"
#include <cassert>
#include <utility>

namespace renn::fiber {

thread_local Fiber* Fiber::current_ = nullptr;

Fiber::Fiber(rt::IExecutor& sched, utils::Routine routine)
    : coro_(std::move(routine)),
      sched_(sched) {}

void Fiber::schedule() {
    sched_.submit(this);
}

void Fiber::run() noexcept {
    step();
}

void Fiber::step() {
    Fiber* prev_fiber = current_;
    current_ = this;

    coro_.resume();

    current_ = prev_fiber;


    /* polling the completion */
    if (coro_.is_done()) {
        /* std::cerr << "DEBUG: Fiber " << this << " Done." << std::endl; */
        delete this;
        return;
    }

    RENN_ASSERT(awaiter_ != nullptr, "Awaiter is nullptr");
    IAwaiter* aw = std::exchange(awaiter_, nullptr);

    aw->on_suspend(FiberHandle(this));
}

void Fiber::suspend(IAwaiter* awaiter) {
    awaiter_ = awaiter;
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
rt::IExecutor& Fiber::current_scheduler() const {
    return sched_;
}
};  // namespace renn::fiber
