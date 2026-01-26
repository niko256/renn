#include "Go.hpp"
#include "../Core/Fiber.hpp"

namespace renn::fiber {

void go(rt::IExecutor& sched, utils::Routine proc) {
    auto newbie = new Fiber(sched, std::move(proc));
    newbie->schedule();
}

void go(utils::Routine proc) {
    go(Fiber::current()->current_scheduler(), std::move(proc));
}

}  // namespace renn::fiber
