#pragma once

#include "../Core/IExecutor.hpp"
#include "../Core/View.hpp"
#include "../Timerrrs/TScheduler.hpp"
#include "../Timerrrs/VClock.hpp"
#include "TimerQueue.hpp"
#include <cstddef>
#include <vvv/list.hpp>

namespace renn::rt {

class SandBox : public IExecutor, public timers::TScheduler {
  public:
    SandBox() = default;

    // Non-copyable, non-movable
    SandBox(const SandBox&) = delete;
    SandBox& operator=(const SandBox&) = delete;

    /* =*= View =*= */
    operator View();

    void submit(RennBase* task) override;

    void set(timers::Duration delay, timers::TimerBase* timer) override;

    size_t run_at_most_tasks(size_t limit);

    bool run_next_task();

    size_t run_tasks();

    size_t fire_ready_timers();

    size_t advance_clock_by(timers::Duration delta);

    size_t advance_clock_to_next_dd();

    size_t run_to_completion();

    size_t run_for(timers::Duration duration);

    bool has_tasks() const;
    bool has_timers() const;
    bool has_pending_work() const;

    bool is_empty() const;
    bool non_empty() const;

    size_t task_count() const;
    size_t timer_count() const;

    timers::Instant current_time() const;

  private:
    timers::VClock clock_;
    vvv::IntrusiveList<RennBase> tasks_;
    SandBoxTimerQueue timers_;
};

}  // namespace renn::rt
