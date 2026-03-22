#pragma once

#include "../Core/Awaiter.hpp"
#include "../Core/Handle.hpp"
#include "../Infra/Time/Time.hpp"
#include "../Infra/Time/TimerBase.hpp"

namespace renn::fiber {

struct SleepAwaiter : IAwaiter, time::TimerBase {
    FiberHandle f;

    void on_suspend(FiberHandle h) override;

    void run() noexcept override;
};

void sleep_for(time::Duration delay);

};  // namespace renn::fiber
