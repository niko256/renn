#pragma once

#include "../../Utils/Routine.hpp"
#include "Task.hpp"
#include <utility>

namespace renn::rt {

struct BoxedTask : TaskBase {
    utils::Routine fun_;

    BoxedTask(const BoxedTask&) = delete;
    BoxedTask(BoxedTask&&) = default;
    BoxedTask& operator=(const BoxedTask&) = delete;
    BoxedTask& operator=(BoxedTask&&) = default;
    explicit BoxedTask(utils::Routine f);

    void run() noexcept override;
};

BoxedTask::BoxedTask(utils::Routine f)
    : fun_(std::move(f)) {}

void BoxedTask::run() noexcept {
    fun_();
    delete this;
}

}  // namespace renn::rt
