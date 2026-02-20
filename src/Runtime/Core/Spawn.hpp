#pragma once

#include "BoxedTask.hpp"
#include "IExecutor.hpp"
#include "Task.hpp"

namespace renn {

/* Fire and forget */
template <typename F>
void spawn(rt::IExecutor& where, F&& owned) {
    where.submit(new rt::BoxedRenn(std::forward<F>(owned)));
}

/* Intrusive */
inline void submit(rt::IExecutor& where, TaskBase* renn) {
    where.submit(renn);
}


}  // namespace renn
