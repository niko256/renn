#pragma once

#include <utility>

namespace renn::future::role {

template <typename Derived>
struct ThunkBase {
    template <typename Combinator>
    [[nodiscard]] auto operator|(Combinator&& comb) &&;

    ThunkBase() = default;
    ~ThunkBase() = default;

    ThunkBase(ThunkBase&&) = default;
    ThunkBase& operator=(ThunkBase&&) = default;

    /* Non-copyable */
    ThunkBase(const ThunkBase&) = delete;
    ThunkBase& operator=(const ThunkBase&) = delete;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename Derived>
struct ComputationBase {
    ComputationBase(ComputationBase&&) = default;
    ComputationBase& operator=(ComputationBase&&) = default;

    ComputationBase(const ComputationBase&) = delete;
    ComputationBase& operator=(const ComputationBase&) = delete;

  protected:
    ComputationBase() = default;
    ~ComputationBase() = default;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename Derived>
template <typename Combinator>
auto ThunkBase<Derived>::operator|(Combinator&& comb) && {
    return std::move(comb).pipe(static_cast<Derived&&>(*this));
}

}  // namespace renn::future::role
