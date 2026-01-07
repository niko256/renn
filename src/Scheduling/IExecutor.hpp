#pragma once

#include "../Utils/Renn.hpp"

namespace renn::sched {

class IExecutor {
  public:
    virtual void submit(renn::Renn&& procedure) = 0;

    virtual ~IExecutor() = default;
};

};  // namespace renn::sched
