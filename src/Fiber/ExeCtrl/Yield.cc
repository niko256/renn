#include "Yield.hpp"
#include "../../Utils/Assert.hpp"
#include "../Core/Fiber.hpp"
#include "../Core/Handle.hpp"

namespace renn::fiber {

void YieldAwaiter::on_suspend(FiberHandle h) {
    h.schedule();
}

void yield() {
    Fiber* c_fib = Fiber::current();
    RENN_ASSERT(c_fib != nullptr, "yield() called outside of fiber context");

    YieldAwaiter awaiter;

    c_fib->suspend(&awaiter);
}

};  // namespace renn::fiber
