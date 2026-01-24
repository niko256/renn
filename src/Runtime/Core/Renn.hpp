#pragma once

#include "vvv/list.hpp"

namespace renn {

struct IRenn {
    virtual void run() noexcept = 0;

  protected:
    ~IRenn() = default;
};

struct RennBase : IRenn, vvv::IntrusiveListNode<RennBase> {
    RennBase() = default;
};

}  // namespace renn
