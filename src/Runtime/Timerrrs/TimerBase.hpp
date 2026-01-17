#pragma once

#include "../Core/Renn.hpp"
#include "Time.hpp"

namespace renn::timers {

/**
 * @brief A timer is just a task with a deadline.
 */
struct TimerBase : public RennBase {
    Timepoint deadline;
};

}  // namespace renn::timers
