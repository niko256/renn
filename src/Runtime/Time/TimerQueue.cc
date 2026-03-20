#include "TimerQueue.hpp"
#include "Time/Time.hpp"
#include "Time/TimerBase.hpp"

namespace renn::time {


void TimerQueue::add_timer(Timepoint deadline, TimerBase* timer) {
    timers_.emplace(deadline, timer);
}

bool TimerQueue::empty() const {
    return timers_.empty();
}

auto TimerQueue::next_deadline() const -> std::optional<time::Timepoint> {
    if (empty()) {
        return std::nullopt;
    }

    return timers_.begin()->first;
}

auto TimerQueue::extract_expired(Timepoint now) -> IntrusiveList<time::TimerBase*> {
    IntrusiveList<time::TimerBase*> ready;

    while (not timers_.empty()) {
        auto timer = timers_.begin();

        if (timer->first <= now) {
            ready.push_back(timer->second);
            timers_.erase(timer);
        } else {
            break;
        }
    }
    return ready;
}

}  // namespace renn::time
