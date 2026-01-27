#pragma once

#include "../Core/Role.hpp"
#include "../Core/Unit.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Computation/Computation.hpp"
#include "../Computation/Immediate.hpp"

namespace renn::future::thunk {

struct [[nodiscard]] Pure : public role::ThunkBase<Pure> {
    using ValueType = Unit;

    Pure() = default;
    Pure(Pure&&) = default;
    Pure& operator=(Pure&&) = default;

    Pure(const Pure&) = delete;
    Pure& operator=(const Pure&) = delete;

    template <Continuation<ValueType> Downstream>
    Computation auto materialize(Downstream d);
};

template <Continuation<typename Pure::ValueType> Downstream>
Computation auto Pure::materialize(Downstream d) {
    return comp::Immediate<typename Pure::ValueType, Downstream>{
        unit, std::move(d)
    };
}
}  // namespace renn::future::thunk
