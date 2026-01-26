#pragma once

#include "../Core/Awaiter.hpp"
#include "../Core/Handle.hpp"
#include "../Runtime/Timerrrs/Time.hpp"
#include "../Runtime/Timerrrs/TimerBase.hpp"

namespace renn::fiber {

struct SleepAwaiter : IAwaiter, timers::TimerBase {
    FiberHandle f;

    void on_suspend(FiberHandle h) override;

    void run() noexcept override;
};

void sleep_for(timers::Duration delay);

};  // namespace renn::fiber
