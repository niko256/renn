#pragma once

#include "Time.hpp"
#include "TimerBase.hpp"
#include <optional>
#include <vvv/list.hpp>

namespace renn::timers {

// Sorted intrusive list of timers
class IntrusiveTimerQueue {
  public:
    void add(TimerBase* timer);

    bool empty() const;

    std::optional<Timepoint> next_deadline() const;

    // Moves expired timers to the provided task list
    bool move_expired_to(Timepoint now, vvv::IntrusiveList<RennBase>& task_queue);

  private:
    vvv::IntrusiveList<TimerBase> list_;
};

}  // namespace renn::timers
