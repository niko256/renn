#include "SleepFor.hpp"
#include "../../Utils/Assert.hpp"
#include "../Core/Fiber.hpp"
#include "../Core/Handle.hpp"

namespace renn::fiber {

void SleepAwaiter::on_suspend(FiberHandle h) {
    /*
     * .
     * ..
     * ...
     */
}

void SleepAwaiter::run() noexcept {
    /* Es ist Zeit... */
    f.schedule();
}

void sleep_for(timers::Duration delay) {
    Fiber* f_curr = Fiber::current();

    RENN_ASSERT(f_curr != nullptr, "Current fiber is invalid...");

    SleepAwaiter slaw;

    f_curr->suspend(&slaw);
}


};  // namespace renn::fiber
