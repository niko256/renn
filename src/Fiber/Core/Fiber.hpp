#pragma once

#include "../../Runtime/Core/IExecutor.hpp"
#include "../../Runtime/Core/Renn.hpp"
#include "../Coroutine/Coro.hpp"
#include "../Utils/Routine.hpp"
#include "Awaiter.hpp"
#include "Handle.hpp"
#include "function2/function2.hpp"
#include <vvv/list.hpp>

namespace renn::fiber {

using SuspendHandler = fu2::unique_function<void(FiberHandle)>;

/*** Fiber = Stackful coroutine x Scheduler ***/

class Fiber : public RennBase {
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

  private:
    renn::Coroutine coro_;
    rt::IExecutor& sched_;
    IAwaiter* awaiter_{};
    static thread_local Fiber* current_;
};

};  // namespace renn::fiber
