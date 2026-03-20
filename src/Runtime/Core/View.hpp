#pragma once

#include "../Timerrrs/TScheduler.hpp"
#include "IExecutor.hpp"
#include "Task.hpp"
#include <tuple>

namespace renn::rt {

struct Env {
    IExecutor* executor_ = nullptr;
    ITimerService* = nullptr;
};

}  // namespace renn::rt
