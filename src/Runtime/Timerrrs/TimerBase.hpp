#pragma once

#include "../Core/Task.hpp"
#include "Time.hpp"
#include <vvv/list.hpp>

namespace renn::timers {

/**
 * @brief A timer is just a task with a deadline.
 */
struct TimerBase : public TaskBase, public vvv::IntrusiveListNode<TimerBase> {
    Timepoint deadline;
};

}  // namespace renn::timers
