#pragma once

#include "../../Utils/Result.hpp"
#include "Future.hpp"
#include "SharedState.hpp"

namespace renn {

template <typename T>
class Promise {

    void produce();


  private:
    SharedState<T>* state_;
    Future<T> future_;
};

/* ///////////////////////////////////////////////////////////// */

};  // namespace renn
