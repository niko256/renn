#pragma once

#include "../../Utils/Routine.hpp"
#include "Task.hpp"
#include <utility>

namespace renn::rt {

struct BoxedRenn : TaskBase {
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
