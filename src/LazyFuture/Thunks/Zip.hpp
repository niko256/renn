#pragma once

#include "../Core/Thunk.hpp"
#include <tuple>
#include "../Trait/ValueOf.hpp"

namespace renn::future::thunk {


template <typename... Inputs>
class [[nodiscard]] Zip : role::ThunkBase<Zip<Inputs...>> {
    using ValueType = std::tuple<trait::ValueOf<Inputs>...>;

    explicit Zip(Inputs... in)
        : inputs_(std::move(in)...) {}

    Zip(Zip&&) = default;
    Zip& operator=(Zip&&) = default;

    Zip(const Zip&) = delete;
    Zip& operator=(const Zip&) = delete;

    /* !... UNIMPLEMENTED ...!
     * .
     * ..
     * ...
     */

  private:
    std::tuple<Inputs...> inputs_;
};

}  // namespace renn::future::thunk
