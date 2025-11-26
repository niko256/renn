#include "Go.hpp"

namespace renn {

void go(renn::sched::IScheduler& sched, renn::Renn&& proc) {
    auto newbie = new renn::Fiber(sched, std::move(proc));
    newbie->schedule();
}

void go(renn::Renn&& proc) {
    go(renn::Fiber::current()->current_scheduler(), std::move(proc));
}

};  // namespace renn
