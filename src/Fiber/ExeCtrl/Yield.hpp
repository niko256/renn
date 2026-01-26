#pragma once

#include "../Core/Awaiter.hpp"
#include "../Core/Handle.hpp"

namespace renn::fiber {

struct YieldAwaiter : IAwaiter {
    void on_suspend(FiberHandle h) override;
};

void yield();

};  // namespace renn::fiber
