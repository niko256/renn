#pragma once

#ifdef RENN_WITH_TWIST

#    include <twist/ed/std/atomic.hpp>
#    include <twist/ed/std/condition_variable.hpp>
#    include <twist/ed/std/mutex.hpp>
#    include <twist/ed/std/thread.hpp>

namespace renn {
namespace stdlike = ::twist::ed::std;
}

#else

#    include <atomic>
#    include <condition_variable>
#    include <mutex>
#    include <thread>

namespace renn {
namespace stdlike = ::std;
}

#endif
