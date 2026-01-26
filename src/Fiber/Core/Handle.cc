#include "Handle.hpp"
#include "Fiber.hpp"
#include <cassert>
#include <utility>

namespace renn {

FiberHandle::FiberHandle(fiber::Fiber* f) : fiber_(f) {}

bool FiberHandle::is_valid() const {
    return fiber_ != nullptr;
}

fiber::Fiber* FiberHandle::release() {
    assert(is_valid());
    return std::exchange(fiber_, nullptr);
}

void FiberHandle::schedule() {
    this->release()->schedule();
}

FiberHandle::FiberHandle(FiberHandle&& other) noexcept : fiber_(std::move(other.fiber_)) {
    other.fiber_ = nullptr;
}

FiberHandle& FiberHandle::operator=(FiberHandle&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    fiber_ = other.fiber_;
    other.fiber_ = nullptr;
    return *this;
}

};  // namespace renn
