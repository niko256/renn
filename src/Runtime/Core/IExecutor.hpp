#pragma once

#include "Renn.hpp"

namespace renn::rt {

class IExecutor {
  public:
    virtual void submit(RennBase*) = 0;

    ~IExecutor() = default;
};

};  // namespace renn::rt
