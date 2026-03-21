#pragma once

#include "Time.hpp"
#include "TimerBase.hpp"

namespace renn::time {

/**
 * @brief Interface for scheduling delayed tasks.
 */
class ITimerService {
  public:
    virtual void set(Duration delay, TimerBase* timer) = 0;

  protected:
    ~ITimerService() = default;
};


};  // namespace renn::time
