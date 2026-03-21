#pragma once

#include <ntrusive/intrusive.hpp>

namespace renn {

struct IRenn {
    virtual void run() noexcept = 0;

  protected:
    ~IRenn() = default;
};

struct TaskBase : IRenn, IntrusiveListNode {
    TaskBase() = default;
};

}  // namespace renn
