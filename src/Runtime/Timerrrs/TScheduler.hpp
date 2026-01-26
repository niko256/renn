#pragma once

#include "Time.hpp"
#include "TimerBase.hpp"

namespace renn::timers {

/**
 * @brief Interface for scheduling delayed tasks.
 */
class TScheduler {
  public:
    virtual void set(Duration delay, TimerBase* timer) = 0;

  protected:
    ~TScheduler() = default;
};


};  // namespace renn::timers
