#pragma once

#include "../Core/Renn.hpp"
#include "../Timerrrs/Time.hpp"
#include "../Timerrrs/TimerBase.hpp"
#include <map>
#include <optional>
#include <vector>

namespace renn::rt {

class SandBoxTimerQueue {
  public:
    void add(timers::Instant deadline, timers::TimerBase* timer);

    bool is_empty() const;

    size_t size() const;

    std::optional<timers::Instant> next_deadline() const;

    std::vector<timers::TimerBase*> extract_ready(timers::Instant now);

  private:
    std::multimap<timers::Instant, timers::TimerBase*> timers_;
};

}  // namespace renn::rt
