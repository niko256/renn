#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../../Runtime/RunLoop/RunLoop.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/Linear.hpp"
#include "../Trait/ValueOf.hpp"
#include <cassert>
#include <optional>

namespace renn::future::thunk {

template <Thunk T>
class [[nodiscard]] Getter : public RennBase, public support::AlmostLinear<Getter<T>> {
  public:
    using ValueType = trait::ValueOf<T>;

    explicit Getter(T th);

    ValueType get();

    void run() noexcept override;

    void set(ValueType v);

  private:
    struct Demand {
        Getter* self_;

        void proceed(ValueType val, rt::State state);
    };

    T thunk_;
    rt::RunLoop looop_;
    std::optional<ValueType> result_;
    bool completed_{false};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <Thunk T>
Getter<T>::Getter(T th) : thunk_(std::move(th)),
                          looop_(),
                          result_(std::nullopt),
                          completed_(false) {}

template <Thunk T>
void Getter<T>::Demand::proceed(ValueType val, rt::State /* state */) {
    self_->set(std::move(val));
}

template <Thunk T>
void Getter<T>::run() noexcept {
    auto comp = thunk_.materialize(Demand{this});
    comp.start(looop_);
}

template <Thunk T>
void Getter<T>::set(ValueType v) {
    result_.emplace(std::move(v));
    completed_ = true;
    looop_.stop();
}

template <Thunk T>
typename Getter<T>::ValueType Getter<T>::get() {
    rt::submit(looop_, this);

    looop_.run();

    assert(completed_);

    return std::move(*result_);
}

}  // namespace renn::future::thunk
