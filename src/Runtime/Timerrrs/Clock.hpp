#pragma once

#include "Time.hpp"
#include <cassert>

namespace renn::timers {

/**
 * @brief Virtual clock..
 */
class Clock {
  public:
    Clock() = default;

    void advance_by(Duration delta);

    void advance_to(Instant point);

    Instant now() const;

  private:
    Instant now_{0};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

void Clock::advance_to(Instant point) {
    assert(point >= now_ && "...cannot go back in time...");
    now_ = point;
}

Instant Clock::now() const {
    return now_;
}

void Clock::advance_by(Duration delta) {
    assert(delta.count() >= 0 && "...cannot go back in time...");
    now_ += delta;
}


}  // namespace renn::timers
