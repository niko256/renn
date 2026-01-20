#pragma once

namespace renn::support {

template <typename Derived>
struct AlmostLinear {
    AlmostLinear() = default;

    AlmostLinear(const AlmostLinear&) = delete;
    AlmostLinear& operator=(const AlmostLinear&) = delete;

    AlmostLinear(AlmostLinear&&) = default;
    AlmostLinear& operator=(AlmostLinear&&) = default;

  protected:
    ~AlmostLinear() = default;
};

}  // namespace renn::support
