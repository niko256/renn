#include "SandBox.hpp"

namespace renn::rt {

SandBox::operator View() {
    return {this, this};
}

void SandBox::submit(RennBase* task) {
    tasks_.PushBack(task);
}

void SandBox::set(timers::Duration delay, timers::TimerBase* timer) {
    timers::Instant deadline = clock_.now() + delay;
    timers_.add(deadline, timer);
}

size_t SandBox::run_at_most_tasks(size_t limit) {
    size_t executed = 0;

    while (executed < limit && !tasks_.IsEmpty()) {
        RennBase* task = tasks_.TryPopFront();
        if (task) {
            task->run();
            ++executed;
        }
    }

    return executed;
}

size_t SandBox::run_tasks() {
    size_t executed = 0;

    while (!tasks_.IsEmpty()) {
        RennBase* task = tasks_.TryPopFront();
        if (task) {
            task->run();
            ++executed;
        }
    }

    return executed;
}

size_t SandBox::fire_ready_timers() {
    auto ready = timers_.extract_ready(clock_.now());

    for (timers::TimerBase* timer : ready) {
        tasks_.PushBack(timer);
    }

    return ready.size();
}

size_t SandBox::advance_clock_by(timers::Duration delta) {
    clock_.advance_by(delta);
    return fire_ready_timers();
}

size_t SandBox::advance_clock_to_next_dd() {
    auto next = timers_.next_deadline();

    if (!next.has_value()) {
        return 0;
    }

    clock_.advance_to(*next);
    return fire_ready_timers();
}

size_t SandBox::run_to_completion() {
    size_t total = 0;

    while (has_pending_work()) {
        total += run_tasks();

        if (!has_tasks() && has_timers()) {
            advance_clock_to_next_dd();
        }
    }

    return total;
}

size_t SandBox::run_for(timers::Duration duration) {
    timers::Instant end_time = clock_.now() + duration;
    size_t total = 0;

    while (true) {
        total += run_tasks();

        auto next = timers_.next_deadline();

        if (!next.has_value() || *next > end_time) {
            clock_.advance_to(end_time);
            break;
        }

        clock_.advance_to(*next);
        fire_ready_timers();
    }

    return total;
}

}  // namespace renn::rt
