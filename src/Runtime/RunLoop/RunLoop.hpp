#pragma once

#include "../Runtime/Core/State.hpp"
#include "../Runtime/Core/View.hpp"
#include "../Timerrrs/TSheduler.hpp"
#include "../Timerrrs/Time.hpp"
#include "../Timerrrs/TimerQueue.hpp"
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <vvv/list.hpp>

namespace renn::rt {

class Runtime : public IExecutor, public timers::TScheduler {
  public:
    using Clock = std::chrono::steady_clock;

    Runtime() = default;

    // Non-copyable, non-movable
    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;
    Runtime(Runtime&&) = delete;
    Runtime& operator=(Runtime&&) = delete;

    operator View();

    void submit(RennBase* renn) override;

    void run();

    void stop();

    void set(timers::Duration delay, timers::TimerBase* timer);

    bool has_work(timers::Timepoint now) const;

  private:
    vvv::IntrusiveList<RennBase> renns_;
    timers::IntrusiveTimerQueue timers_;

    std::mutex mtx_;
    std::condition_variable condvar_;

    bool stop_requested_{false};
};

};  // namespace renn::rt
