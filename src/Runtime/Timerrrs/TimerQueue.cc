#include "TimerQueue.hpp"

namespace renn::timers {

void IntrusiveTimerQueue::add(TimerBase* timer) {
    auto it = list_.Begin();
    while (it != list_.End()) {
        if (it->deadline > timer->deadline) {
            break;
        }
        ++it;
    }
    list_.Insert(it, timer);
}

bool IntrusiveTimerQueue::empty() const {
    return list_.IsEmpty();
}

std::optional<Timepoint> IntrusiveTimerQueue::next_deadline() const {
    if (list_.IsEmpty())
        return std::nullopt;
    return list_.Front()->deadline;
}

// Moves expired timers to the provided task list
bool IntrusiveTimerQueue::move_expired_to(Timepoint now, vvv::IntrusiveList<RennBase>& task_queue) {
    bool moved = false;
    while (!list_.IsEmpty()) {
        TimerBase* t = list_.Front();
        if (t->deadline <= now) {
            list_.PopFront();
            task_queue.PushBack(t);
            moved = true;
        } else {
            break;
        }
    }
    return moved;
}

}  // namespace renn::timers
