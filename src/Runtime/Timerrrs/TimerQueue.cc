#include "TimerQueue.hpp"

namespace renn::timers {

  void IntrusiveTimerQueue::add(TimerBase* timer) {
      list_.push_back(*timer);
  }

bool IntrusiveTimerQueue::empty() const {
    return list_.empty();
}

std::optional<Timepoint> IntrusiveTimerQueue::next_deadline() const {
    if (list_.empty()) {
        return std::nullopt;
    }

    const TimerBase& front = list_.front();
    return front.deadline;
}

bool IntrusiveTimerQueue::move_expired_to(Timepoint now, IntrusiveList<TaskBase>& task_queue) {
    bool moved = false;

    while (!list_.empty()) {
        TimerBase& t = list_.front();

        if (t.deadline <= now) {
            list_.pop_front();
            task_queue.push_back(t); /* TimerBase* -> RennBase* (upcast) */
            moved = true;
        } else {
            break;
        }
    }

    return moved;
}

}  // namespace renn::timers
