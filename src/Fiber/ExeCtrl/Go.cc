#include "Go.hpp"
#include "../Core/Fiber.hpp"
#include "Core/Env.hpp"
#include "Core/IExecutor.hpp"

namespace renn::fiber {

void go(rt::Env sched, utils::Routine proc) {
    auto newbie = new Fiber(sched, std::move(proc));
    newbie->schedule();
}

void go(utils::Routine proc) {
    go(rt::Env::from(Fiber::current()->current_scheduler()), std::move(proc));
}

}  // namespace renn::fiber
