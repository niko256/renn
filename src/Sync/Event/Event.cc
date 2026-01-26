#include "Event.hpp"

namespace renn::sync {

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

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

};  // namespace renn::sync
