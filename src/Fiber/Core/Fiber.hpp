#pragma once

#include "../Coroutine/Coro.hpp"
#include "../Coroutine/Routine.hpp"
#include "../Scheduling/IExecutor.hpp"
#include "Handle.hpp"
#include "Syscalls.hpp"
#include "function2/function2.hpp"
#include <vvv/list.hpp>

namespace renn {

using SuspendHandler = fu2::unique_function<void(FiberHandle)>;

/*** Fiber = Stackful coroutine x Scheduler ***/

class Fiber : public vvv::IntrusiveListNode<Fiber> {
  public:
    explicit Fiber(sched::IExecutor&, Routine);

    void schedule();

    void step();

    void suspend(Syscall reason, SuspendHandler sc_handler);

    static void set_current(Fiber*);

    static Fiber* current();

    Coroutine& get_coro();

    [[nodiscard]] sched::IExecutor& current_scheduler() const;

  private:
    renn::Coroutine coro_;
    sched::IExecutor& sched_;
    Syscall reason_;
    SuspendHandler handler_;
    static thread_local Fiber* current_;
};

};  // namespace renn
