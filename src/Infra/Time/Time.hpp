#pragma once

#include <chrono>

namespace renn::time {

/* Duration type for delays */
using Duration = std::chrono::milliseconds;

/* System general clock */
using SystemClock = std::chrono::steady_clock;

using Timepoint = std::chrono::steady_clock::time_point;

};  // namespace renn::time
