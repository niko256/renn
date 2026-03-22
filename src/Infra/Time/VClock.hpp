#pragma once

#include "Time/Time.hpp"
#include "Utils/Assert.hpp"

namespace renn::time {


class VirtualClock final {
  private:
    time::Timepoint now_{};

  public:
    VirtualClock() = default;

    time::Timepoint now() const {
        return now_;
    }

    void advance_by(time::Duration delta) {
        RENN_ASSERT(delta.count() >= 0, "cannot go back in time...");
        now_ += delta;
    }

    void advance_to(time::Timepoint point) {
        RENN_ASSERT(point >= now_, "cannot go back in time...");
        now_ = point;
    }
};

}  // namespace renn::time
