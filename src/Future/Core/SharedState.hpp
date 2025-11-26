#pragma once

#include "../../Utils/Callback.hpp"
#include "../../Utils/Result.hpp"
#include "StateMachine.hpp"

namespace renn {

template <typename T>
class SharedState {
  public:
    void consume(renn::Callback<T> cb);

    void produce();

  private:
    void date();

  private:
    StateMachine state_;
    utils::Result<T> result_;
    Callback<T> callback_;
};

/* ///////////////////////////////////////////////////////////// */

};  // namespace renn
