#pragma once

#include "../../Runtime/Core/Renn.hpp"
#include "../../Runtime/RunLoop/RunLoop.hpp"
#include "../Core/Thunk.hpp"
#include "../Trait/ValueOf.hpp"
#include "../Trait/ComputationOf.hpp"
#include <cassert>
#include <optional>

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
    struct Demand {
        Receiver* self_;

        void proceed(ValueType val, rt::State state);
    };

    using Comp = trait::ComputationOf<T, Demand>;

    std::optional<Comp> comp_;
    T thunk_;
    rt::RunLoop looop_;
    std::optional<ValueType> result_;
    bool completed_{false};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <Thunk T>
Receiver<T>::Receiver(T th)
    : thunk_(std::move(th)),
      looop_(),
      result_(std::nullopt),
      completed_(false) {}

template <Thunk T>
void Receiver<T>::Demand::proceed(ValueType val, rt::State /* state */) {
    self_->set(std::move(val));
}

template <Thunk T>
void Receiver<T>::run() noexcept {
    comp_.emplace(thunk_.materialize(Demand{this}));

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

    looop_.run();

    assert(completed_);

    return std::move(*result_);
}

}  // namespace renn::future::thunk
