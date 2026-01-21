#pragma once

#include "Time.hpp"
#include <cassert>

namespace renn::timers {

/**
 * @brief Virtual clock..
 */
class VClock {
  public:
    VClock() = default;

    void advance_by(Duration delta);

    void advance_to(Instant point);

    Instant now() const;

  private:
    Instant now_{0};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

void VClock::advance_to(Instant point) {
    assert(point >= now_ && "...cannot go back in time...");
    now_ = point;
}

Instant VClock::now() const {
    return now_;
}

void VClock::advance_by(Duration delta) {
    assert(delta.count() >= 0 && "...cannot go back in time...");
    now_ += delta;
}


}  // namespace renn::timers
