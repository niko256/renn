#pragma once

#include "../../Utils/Assert.hpp"
#include "../../Utils/Result.hpp"
#include "SharedState.hpp"
#include <exception>
#include <expected>
#include <future>
#include <utility>

namespace renn::tryst {

template <typename T>
class Promise {
  public:
    explicit Promise(SharedState<T>* s);

    /* Move-constructible */
    Promise(Promise&& other) noexcept;

    Promise& operator=(Promise&&) = delete;
    Promise& operator=(const Promise&) = delete;
    Promise(const Promise&) = delete;

    ~Promise();

    /* One-shot */
    void set(T value);

    SharedState<T>* no_state();

    bool has_state() const;

    [[nodiscard]] SharedState<T>* release_state();

    [[nodiscard]] SharedState<T>* satisfy_state();

    SharedState<T>* satisfied_state();


  private:
    SharedState<T>* state_;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename T>
Promise<T>::Promise(SharedState<T>* s) : state_(s) {}

template <typename T>
Promise<T>::Promise(Promise&& other) noexcept : state_(other.release_state()) {}

template <typename T>
void Promise<T>::set(T value) {
    RENN_ASSERT(has_state(), "Promise has no state");

    SharedState<T>* state = std::exchange(state_, no_state());

    state->produce(utils::Result<T>{std::move(value)});
}

template <typename T>
Promise<T>::~Promise<T>() {
    if (has_state()) {
        auto e_ptr = std::make_exception_ptr(std::future_error(std::future_errc::broken_promise));

        state_->produce(utils::Result<T>{std::unexpected(e_ptr)});
    }
}

template <typename T>
SharedState<T>* Promise<T>::no_state() {
    return nullptr;
}

template <typename T>
bool Promise<T>::has_state() const {
    return (state_ != no_state()) && (state_ != satisfied_state());
}

template <typename T>
SharedState<T>* Promise<T>::release_state() {
    return std::exchange(state_, no_state());
}

template <typename T>
SharedState<T>* Promise<T>::satisfied_state() {
    return reinterpret_cast<SharedState<T>*>(1);
}

template <typename T>
SharedState<T>* Promise<T>::satisfy_state() {
    RENN_ASSERT(has_state(), "Promise has no state");
}

};  // namespace renn::tryst
