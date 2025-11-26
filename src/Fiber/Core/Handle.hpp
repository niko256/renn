#pragma once

#include "Fiber.hpp"

namespace renn {

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
    renn::Fiber* fiber_ = nullptr;
};

};  // namespace renn
