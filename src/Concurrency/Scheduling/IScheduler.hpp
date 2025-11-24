#pragma once

#include "Task.hpp"

namespace ds::runtime::sched {

class IScheduler {
  public:
    virtual void submit(ds::runtime::task::Task&& procedure) = 0;

    virtual ~IScheduler() = default;
};

};  // namespace ds::runtime::sched
