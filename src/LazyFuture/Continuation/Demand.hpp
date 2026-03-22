#pragma once

#include "Continuation.hpp"
#include "Core/Env.hpp"

namespace renn::future::cont {

template <typename V, typename Receiver>
class Demand : public role::ContinuationTag {
  private:
    /* +---+---+---+---+ */

    Receiver* receiver_;

    /* +---+---+---+---+ */
  public:
    using ValueType = V;

    explicit Demand(Receiver* r);

    Demand(Demand&&) = default;

    Demand(const Demand&) = delete;

    void proceed(V value, rt::Env st);
};

template <typename V, typename Receiver>
Demand<V, Receiver>::Demand(Receiver* r)
    : receiver_(r) {}

template <typename V, typename Receiver>
void Demand<V, Receiver>::proceed(V value, rt::Env /* st */) {
    receiver_->set(std::move(value));
}

}  // namespace renn::future::cont
