#pragma once

#include <utility>

namespace renn::future::role {

template <typename Derived>
struct ThunkBase {
    template <typename Combinator>
    auto operator|(Combinator&& thunk) &&;

    ThunkBase() = default;
    ThunkBase(ThunkBase&&) = default;
    ~ThunkBase() = default;

    /* Non-copyable */
    ThunkBase(const ThunkBase&) = delete;
    ThunkBase& operator=(const ThunkBase&) = delete;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename Derived>
struct ComputationBase {
    ComputationBase(ComputationBase&&) = delete;
    ComputationBase(const ComputationBase&) = delete;
    ComputationBase& operator=(ComputationBase&&) = delete;
    ComputationBase& operator=(const ComputationBase&) = delete;

  protected:
    ComputationBase() = default;
    ~ComputationBase() = default;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename Derived>
template <typename Combinator>
auto ThunkBase<Derived>::operator|(Combinator comb) && {
    return std::move(comb).pipe(static_cast<Derived&&>(*this));
}

}  // namespace renn::future::role
