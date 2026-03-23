#pragma once

#include <function2/function2.hpp>

namespace renn::sync {

class [[nodiscard]] Defer {
  private:
    /* +---+---+---+---+---+---+---+---+---+ */

    fu2::unique_function<void()> callback_;

    /* +---+---+---+---+---+---+---+---+---+ */

  public:
    explicit Defer(fu2::unique_function<void()> cb)
        : callback_(std::move(cb)) {}

    ~Defer();

    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;

    Defer(Defer&& oth) noexcept
        : callback_(std::move(oth.callback_)) {}

    Defer& operator=(Defer&& oth) noexcept {
        if (this != &oth) {
            if (callback_) {
                callback_();
            }
            callback_ = std::move(oth.callback_);
        }
        return *this;
    }
};

}  // namespace renn::sync
