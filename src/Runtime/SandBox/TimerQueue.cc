#include "TimerQueue.hpp"

namespace renn::rt {

void SandBoxTimerQueue::add(Instant deadline, TimerBase* timer) {
    timers_.emplace(deadline, timer);
}

bool SandBoxTimerQueue::is_empty() const {
    return timers_.empty();
}

size_t SandBoxTimerQueue::size() const {
    return timers_.size();
}

std::optional<Instant> SandBoxTimerQueue::next_deadline() const {
    if (is_empty()) {
        return std::nullopt;
    }
    return timers_.begin()->first;
}

std::vector<TimerBase*> SandBoxTimerQueue::extract_ready(Instant now) {
    std::vector<timer::TimerBase*> ready_tmrs;

    while (!is_empty()) {
        auto it = timers_.begin();

        if (it->first <= now) {
            ready_tmrs.push_back(it->second);
            timers_.erase(it);
        } else {
            break;
        }
    }

    return ready_tmrs;
}

}  // namespace renn::rt
