#pragma once

#include <atomic>
#include <futex_like/wait_wake.hpp>

namespace renn {

class Event {
  public:
    void wait();

    void fire();

  private:
    std::atomic_uint32_t ready_{0};
};

//////////////////////////////////////////////////////////////////////

void Event::wait() {
    while (!ready_.load()) {
        futex_like::WaitOnce(ready_, 0);
    }
}

void Event::fire() {
    auto wake_key = futex_like::PrepareWake(ready_);
    ready_.store(1);
    futex_like::WakeAll(wake_key);
}

};  // namespace renn
