#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../Continuation/Continuation.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Continuation/Transform.hpp"
#include <algorithm>
#include <optional>
#include <type_traits>

namespace renn::future::thunk {

/*
 * | Future<T> -> (T -> U) -> Future<U> |
 */
template <Thunk Upstream, typename F>
struct [[nodiscard]] Map : public role::ThunkBase<Map<Upstream, F>> {
    using InputType = trait::ValueOf<Upstream>;
    using OutputType = std::invoke_result_t<F, InputType>;

    using ValueType = OutputType;

    Upstream producer_;
    F procedure_;

    Map(Upstream pr, F user)
        : producer_(std::move(pr)),
          procedure_(std::move(user)) {}

    template <Continuation<OutputType> Downstream>
    Computation auto materialize(Downstream cont) {
        auto transformer
            = cont::Transform<InputType, OutputType, F, Downstream>{
                std::move(procedure_), std::move(cont)
            };

        /* let producer wrap up and materialize continuation of this stage */
        return producer_.materialize(std::move(transformer));
    }
};

}  // namespace renn::future::thunk
