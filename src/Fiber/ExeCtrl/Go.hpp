#pragma once

#include "../Utils/Renn.hpp"
#include "Fiber.hpp"

namespace renn {

void go(renn::sched::IScheduler&, renn::Renn&&);

void go(renn::Renn&&);

};  // namespace renn
