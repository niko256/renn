#pragma once

namespace renn::fiber {

/* forward-declaration */
class Fiber;

}  // namespace renn::fiber

namespace renn {

class FiberHandle {
  public:
    explicit FiberHandle(fiber::Fiber* fiber);

    FiberHandle() = default;

    ~FiberHandle() = default;

    FiberHandle(const FiberHandle&) = delete;

    FiberHandle& operator=(const FiberHandle&) = delete;

    FiberHandle(FiberHandle&& other) noexcept;

    FiberHandle& operator=(FiberHandle&& other) noexcept;

    bool is_valid() const;

    fiber::Fiber* release();

    void schedule();

  private:
    fiber::Fiber* fiber_ = nullptr;
};

};  // namespace renn
