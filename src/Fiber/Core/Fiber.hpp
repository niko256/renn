#pragma once

#include "../Coroutine/Coro.hpp"
#include "../Coroutine/Routine.hpp"
#include "../Scheduling/IScheduler.hpp"
#include <vvv/list.hpp>

namespace renn {

// Fiber = Stackful coroutine x Scheduler

class Fiber : public vvv::IntrusiveListNode<Fiber> {
  private:
    renn::Coroutine coro_;
    sched::IScheduler& sched_;

    static thread_local Fiber* current_;

  public:
    explicit Fiber(sched::IScheduler&, Routine);

    void schedule();

    void step();

    static void set_current(Fiber*);

    static Fiber* current();

    Coroutine& get_coro();

    [[nodiscard]] sched::IScheduler& current_scheduler() const;
};

};  // namespace renn
