#pragma once

#include "vvv/list.hpp"

namespace renn {

struct IRenn {
    virtual void run() noexcept = 0;

  protected:
    ~IRenn() = default;
};

struct TaskBase : IRenn, vvv::IntrusiveListNode<TaskBase> {
    TaskBase() = default;
};

}  // namespace renn
