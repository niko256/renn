#pragma once

#include "Time.hpp"
#include <chrono>

namespace renn::time {


struct IClock {
    virtual time::Timepoint now() const = 0;
    virtual ~IClock() = default;
};

class SteadyClock final : public IClock {
    time::Timepoint now() const override {
        return std::chrono::steady_clock::now();
    }
};

};  // namespace renn::time
