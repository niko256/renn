#include "TimerQueue.hpp"

namespace renn::timers {

void IntrusiveTimerQueue::add(TimerBase* timer) {
    list_.PushBack(timer);
}

bool IntrusiveTimerQueue::empty() const {
    return list_.IsEmpty();
}

std::optional<Timepoint> IntrusiveTimerQueue::next_deadline() const {
    if (list_.IsEmpty()) {
        return std::nullopt;
    }

    TimerBase* min_timer = nullptr;
    Timepoint min_deadline = Timepoint::max();

    const TimerBase* front = list_.TryFront();
    if (front) {
        return front->deadline;
    }
    return std::nullopt;
}

bool IntrusiveTimerQueue::move_expired_to(Timepoint now, vvv::IntrusiveList<RennBase>& task_queue) {
    bool moved = false;

    while (!list_.IsEmpty()) {
        TimerBase* t = list_.TryFront();
        if (t && t->deadline <= now) {
            list_.TryPopFront();
            task_queue.PushBack(t); /* TimerBase* -> RennBase* (upcast) */
            moved = true;
        } else {
            break;
        }
    }

    return moved;
}

}  // namespace renn::timers
