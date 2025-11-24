#pragma once

#include "../Scheduling/Task.hpp"
#include "Fiber.hpp"

namespace ds::fiber {

void go(runtime::Scheduler&, runtime::task::Task&&);

void go(runtime::task::Task&&);

};  // namespace ds::fiber
