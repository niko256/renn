#pragma once

namespace renn {

class Fiber;

class FiberHandle {
  public:
    explicit FiberHandle(Fiber* fiber);

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
    renn::Fiber* fiber_ = nullptr;
};

};  // namespace renn
