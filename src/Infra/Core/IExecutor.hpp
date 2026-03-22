#pragma once

#include "Task.hpp"

namespace renn::rt {

class IExecutor {
  public:
    virtual void submit(TaskBase*) = 0;

    ~IExecutor() = default;
};

};  // namespace renn::rt
