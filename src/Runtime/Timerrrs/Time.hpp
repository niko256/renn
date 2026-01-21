#pragma once

#include <chrono>

namespace renn::timers {

/* Duration type for delays */
using Duration = std::chrono::milliseconds;

/* System general clock */
using SystemClock = std::chrono::steady_clock;

using Timepoint = std::chrono::steady_clock::time_point;

/* virtual time for SandBox */
using Instant = Duration;

};  // namespace renn::timers
