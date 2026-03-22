#pragma once

#include "../../Utils/StdLike.hpp"
#include <futex_like/wait_wake.hpp>

namespace renn::sync {

class Event {
  private:
    /* +---+---+---+---+---+---+---+ */

    stdlike::atomic_uint32_t ready_{0};

    /* +---+---+---+---+---+---+---+ */

  public:
    void wait();

    void fire();
};

};  // namespace renn::sync
