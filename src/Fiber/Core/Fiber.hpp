#pragma once

#include "../../Infra/Core/IExecutor.hpp"
#include "../../Infra/Core/Task.hpp"
#include "../Coroutine/Coro.hpp"
#include "../Utils/Routine.hpp"
#include "Awaiter.hpp"
#include "Handle.hpp"
#include "function2/function2.hpp"

namespace renn::fiber {

using SuspendHandler = fu2::unique_function<void(FiberHandle)>;

/*** Fiber = Stackful coroutine x Scheduler ***/

class Fiber : public TaskBase {
  private:
    /* +---+---+---+---+---+---+---+---+ */

    renn::Coroutine coro_;
    rt::IExecutor& sched_;
    IAwaiter* awaiter_{};
    static thread_local Fiber* current_;

    /* +---+---+---+---+---+---+---+---+ */

  public:
    explicit Fiber(rt::IExecutor&, utils::Routine);

    void schedule();
    void run() noexcept override;

    void suspend(IAwaiter*);

    static void set_current(Fiber*);
    static Fiber* current();

    Coroutine& get_coro();
    [[nodiscard]] rt::IExecutor& current_scheduler() const;

  private:
    void step();
};

};  // namespace renn::fiber
