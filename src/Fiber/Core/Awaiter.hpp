#pragma once

#include "Handle.hpp"

namespace renn::fiber {

struct IAwaiter {
    virtual void on_suspend(FiberHandle h) = 0;

  protected:
    ~IAwaiter() = default;
};


}  // namespace renn::fiber
