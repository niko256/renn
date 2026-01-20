#pragma once

#include "../../Utils/Routine.hpp"
#include "Renn.hpp"
#include <utility>

namespace renn::rt {

struct BoxedRenn : RennBase {
    utils::Routine fun_;

    explicit BoxedRenn(utils::Routine f);

    void run() noexcept override;
};

BoxedRenn::BoxedRenn(utils::Routine f) : fun_(std::move(f)) {}

void BoxedRenn::run() noexcept {
    fun_();
    delete this;
}

}  // namespace renn::rt
