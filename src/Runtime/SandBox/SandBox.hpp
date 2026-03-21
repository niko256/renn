#pragma once

#include "../Core/IExecutor.hpp"
#include "../Time/ITimerService.hpp"
#include "../Time/VClock.hpp"
#include "Time/Time.hpp"
#include "Time/TimerQueue.hpp"
#include <cstddef>
#include <ntrusive/intrusive.hpp>

namespace renn::rt {


/*
 * @brief A single-threaded runtime environment
 * for deterministing simulation
 */
class SandBox : public IExecutor, public time::ITimerService {
  private:
    time::VirtualClock clock_;
    IntrusiveList<TaskBase> tasks_;
    time::TimerQueue timers_;

  public:
    SandBox() = default;

    // Non-copyable, non-movable
    SandBox(const SandBox&) = delete;
    SandBox& operator=(const SandBox&) = delete;

    SandBox(SandBox&&) noexcept = delete;
    SandBox& operator=(SandBox&&) noexcept = delete;

    void submit(TaskBase* task) override;
    void set(time::Duration delay, time::TimerBase* timer) override;

    size_t run_at_most_tasks(size_t limit);
    bool run_next_task();
    size_t run_tasks();

    size_t fire_ready_timers();
    size_t advance_clock_by(time::Duration delta);
    size_t advance_clock_to_next_dd();

    size_t run_to_completion();
    size_t run_for(time::Duration duration);

    bool has_tasks() const;
    bool has_timers() const;
    bool has_pending_work() const;

    bool is_empty() const;
    bool non_empty() const;

    size_t task_count() const;
    size_t timer_count() const;

    auto current_time() const -> time::Timepoint;
};

}  // namespace renn::rt
