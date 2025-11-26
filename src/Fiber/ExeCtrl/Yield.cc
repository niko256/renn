#include "Yield.hpp"

namespace renn::fiber {

void yield() {
    auto f = renn::Fiber::current();
    f->get_coro().suspend();
}

};  // namespace renn::fiber
