#pragma once

#include "../../Utils/Routine.hpp"
#include "Task.hpp"
#include <utility>

namespace renn::rt {

struct BoxedRenn : TaskBase {
    utils::Routine fun_;

    BoxedRenn(const BoxedRenn&) = delete;
    BoxedRenn(BoxedRenn&&) = default;
    BoxedRenn& operator=(const BoxedRenn&) = delete;
    BoxedRenn& operator=(BoxedRenn&&) = default;
    explicit BoxedRenn(utils::Routine f);

    void run() noexcept override;
};

BoxedRenn::BoxedRenn(utils::Routine f)
    : fun_(std::move(f)) {}

void BoxedRenn::run() noexcept {
    fun_();
    delete this;
}

}  // namespace renn::rt
