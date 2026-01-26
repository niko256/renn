#pragma once

#include "Callback.hpp"
#include "SharedState.hpp"
#include <../../Utils/Result.hpp>
#include <utility>

namespace renn::tryst {

/**
 * @class Future
 *
 * Once created, future can be moved but no be copied,
 *    ensuring single ownership of the result
 *
 * @tparam T represents the value expected from the async operation
 */

template <typename T>
class Future {
  public:
    explicit Future(SharedState<T>*);

    // Move-constructible
    Future(Future&&) noexcept;

    // Non-copyable
    Future(const Future&) = delete;
    Future& operator=(const Future&) = delete;

    // Non-move-assignable
    Future& operator=(Future&&) = delete;

    ~Future();

    /**
     * @brief Registers a callback to consume the result when available.
     *
     * => callback will be invoked when the Promise produces the result
     *
     * @pre Future must be valid (has an associated SharedState).
     * @post Future is moved from and no longer valid (one-shot).
     */
    void consume(Callback<T>) &&;

    bool valid() const;

    /**
     * @brief Releases ownership without consuming the result.
     * => Useful if you want to discard a Future without waiting for the result.
     */
    void reset();


    /**
     * @brief Transfer ownership of the shared state to the caller
     * @post this->valid() == false.
     */
    SharedState<T>* release_state();

  private:
    SharedState<T>* state_;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */


template <typename T>
Future<T>::Future(SharedState<T>* state)
    : state_(state) {}

template <typename T>
void Future<T>::consume(Callback<T> cb) && {
    RENN_ASSERT(valid(), "Future::consume called on invalid future");

    auto adapter = [cb = std::move(cb)](utils::Result<T> res) mutable {
        try {
            if (res.has_value()) {
                cb(std::move(*res));
            }
        } catch (...) {
            std::terminate();
        }
    };

    auto utilize = release_state();

    utilize->consume(std::move(adapter));
}

template <typename T>
Future<T>::Future(Future&& other) noexcept
    : state_(std::exchange(other.state_, nullptr)) {}

template <typename T>
Future<T>::~Future<T>() {
    if (valid()) {
        reset();
    }
}

template <typename T>
bool Future<T>::valid() const {
    return state_ != nullptr;
}

template <typename T>
SharedState<T>* Future<T>::release_state() {
    return std::exchange(state_, nullptr);
}

template <typename T>
void Future<T>::reset() {
    release_state()->consume([](utils::Result<T>) {});
}

};  // namespace renn::tryst
