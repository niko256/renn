#pragma once

#include "Fiber.hpp"

namespace ds::runtime {

class FiberHandle {
  public:
    FiberHandle() = default;

    ~FiberHandle() = default;

    FiberHandle(const FiberHandle&) = delete;

    FiberHandle& operator=(const FiberHandle&) = delete;

    FiberHandle(FiberHandle&& other) noexcept;

    FiberHandle& operator=(FiberHandle&& other) noexcept;

    bool is_valid() const;

    Fiber* release();

    void schedule();

  private:
    FiberHandle(Fiber* fiber) : fiber_(fiber) {}

  private:
    ds::runtime::Fiber* fiber_ = nullptr;
};

};  // namespace ds::runtime
