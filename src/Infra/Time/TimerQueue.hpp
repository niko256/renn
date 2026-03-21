#pragma once

#include "Time.hpp"
#include "TimerBase.hpp"
#include <map>
#include <optional>
#include <ntrusive/intrusive.hpp>

namespace renn::time {

class TimerQueue {
  private:
    /* *---*---*---*---*---*---*---*---*---*---*---*---*---*---* */

    std::multimap<time::Timepoint, time::TimerBase*> timers_;

    /* *---*---*---*---*---*---*---*---*---*---*---*---*---*---* */

  public:
    void add_timer(Timepoint deadline, TimerBase* timer);

    bool empty() const;

    auto next_deadline() const -> std::optional<time::Timepoint>;

    /*
     * @brief Extract all timers with deadline <= now()
     */
    auto extract_expired(Timepoint now) -> IntrusiveList<time::TimerBase*>;
};

}  // namespace renn::time
