#include "TimerQueue.hpp"

namespace renn::rt {

void SandBoxTimerQueue::add(timers::Instant deadline, timers::TimerBase* timer) {
    timers_.emplace(deadline, timer);
}

bool SandBoxTimerQueue::is_empty() const {
    return timers_.empty();
}

size_t SandBoxTimerQueue::size() const {
    return timers_.size();
}

std::optional<timers::Instant> SandBoxTimerQueue::next_deadline() const {
    if (is_empty()) {
        return std::nullopt;
    }
    return timers_.begin()->first;
}

std::vector<timers::TimerBase*> SandBoxTimerQueue::extract_ready(timers::Instant now) {
    std::vector<timers::TimerBase*> ready_tmrs;

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
