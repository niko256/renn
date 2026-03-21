#pragma once

#include "Core/IExecutor.hpp"
#include "Time/IClock.hpp"
#include "Time/ITimerService.hpp"

namespace renn::rt {

struct RennServices {
    IExecutor* executor_ = nullptr;
    time::ITimerService* timers_ = nullptr;
    time::IClock* clock_ = nullptr;
};

struct State {
    RennServices services_;
    /* ... */
};

}  // namespace renn::rt
