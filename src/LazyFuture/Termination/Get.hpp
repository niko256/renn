#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../../Runtime/RunLoop/RunLoop.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Trait/ComputationOf.hpp"
#include <cassert>
#include <optional>
#include "../Continuation/Demand.hpp"

namespace renn::future::thunk {

template <Thunk T>
class [[nodiscard]] Receiver : public RennBase {
  public:
    using ValueType = trait::ValueOf<T>;

    explicit Receiver(T th);

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    ValueType get();

    void run() noexcept override;

    void set(ValueType v);

  private:
    using MyDemand = cont::Demand<ValueType, Receiver>;
    using Comp = trait::ComputationOf<T, MyDemand>;

    T thunk_;
    rt::RunLoop looop_;
    std::optional<Comp> comp_;
    std::optional<ValueType> result_;
    bool completed_{false};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <thunk::Thunk T>
Receiver<T>::Receiver(T thunk)
    : thunk_(std::move(thunk)),
      looop_(),
      comp_(std::nullopt),
      result_(std::nullopt),
      completed_(false) {}

template <Thunk T>
void Receiver<T>::run() noexcept {
    comp_.emplace(std::move(thunk_).materialize(MyDemand{this}));

    comp_->start(looop_);
}

template <Thunk T>
void Receiver<T>::set(ValueType v) {
    result_.emplace(std::move(v));
    completed_ = true;

    looop_.stop();
}

template <Thunk T>
typename Receiver<T>::ValueType Receiver<T>::get() {
    rt::submit(looop_, this);

    /* spinning looooop */
    looop_.run();

    assert(completed_);

    return std::move(*result_);
}

}  // namespace renn::future::thunk
