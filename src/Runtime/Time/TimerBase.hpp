#pragma once

#include "../Core/Task.hpp"
#include "Time.hpp"
#include <ntrusive/intrusive.hpp>

namespace renn::time {

/**
 * @brief A timer is just a task with a deadline.
 */
struct TimerBase : public TaskBase {
    Timepoint deadline;
};

}  // namespace renn::time
