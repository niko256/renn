#pragma once

#include "Core/IExecutor.hpp"
#include "Time/IClock.hpp"
#include "Time/ITimerService.hpp"
#include <concepts>
#include <optional>
#include <tuple>

namespace renn::rt {


template <typename... Services>
class State {
  private:
    /* +---+---+---+---+---+---+---+---+---+ */

    std::tuple<Services*...> slots_;

    /* +---+---+---+---+---+---+---+---+---+ */

  public:
    constexpr State()
        : slots_(static_cast<Services*>(nullptr)...) {}

    static constexpr auto empty() -> State {
        return State{};
    }

    template <typename... Ts>
        requires((std::same_as<Ts, Services> and ...))
    static auto from(Ts&... services) -> State {
        State s;
        ((std::get<Ts*>(s.slots_) = &services), ...);

        return s;
    }

    template <typename S>
        requires(std::same_as<S, Services> || ...)
    /**
     * @brief Constraint ensuring the type T is one of the services managed by this State.
     * The `|| ...` is a fold expression. It performs a logical OR across the pack expansion
     * It returns true if T matches any type in the Services pack.
     */
    auto get() const -> S& {
        S* p = std::get<S*>(slots_);
        RENN_ASSERT(p != nullptr, "[State] : this service isn't provided...");
        return *p;
    }

    template <typename S>
        requires(std::same_as<S, Services> || ...)
    auto try_get() -> std::optional<S*> {
        return std::get<S*>(slots_);
    }

    template <typename S>
        requires(std::same_as<S, Services> || ...)
    auto with(S& service) const -> State {
        auto& copy = *this;
        std::get<S*>(copy.slots_) = &service;

        return copy;
    }

    auto operator+(const State& rhs) const -> State {
        State out;

        ((std::get<Services*>(out.slots_) = std::get<Services*>(rhs.slots_)
                                                ? std::get<Services*>(rhs.slots_)
                                                : std::get<Services*>(this->slots_)),
         ...);
    }

    template <typename S>
        requires(std::same_as<S, Services> || ...)
    auto has() const -> bool {
        return std::get<S*>(slots_) != nullptr;
    }

    auto complete() const -> bool {
        return (... and (std::get<Services*>(slots_) != nullptr));
    }
};

}  // namespace renn::rt
