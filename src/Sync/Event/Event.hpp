#pragma once

#include <atomic>
#include <futex_like/wait_wake.hpp>

namespace renn::sync {

class Event {
  private:
    /* +---+---+---+---+---+---+---+ */

    std::atomic_uint32_t ready_{0};

    /* +---+---+---+---+---+---+---+ */

  public:
    void wait();

    void fire();
};

};  // namespace renn::sync
