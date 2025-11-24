#include "Go.hpp"

namespace ds::fiber {

void go(ds::runtime::Scheduler& sched, runtime::task::Task&& proc) {
    auto newbie = new ds::runtime::Fiber(sched, std::move(proc));
    newbie->schedule();
}

void go(runtime::task::Task&& proc) {
    go(ds::runtime::Fiber::current()->current_scheduler(), std::move(proc));
}

};  // namespace ds::fiber
