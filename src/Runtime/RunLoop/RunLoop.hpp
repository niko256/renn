#pragma once

#include "../Core/View.hpp"
#include "../Timerrrs/TScheduler.hpp"
#include "../Timerrrs/Time.hpp"
#include "../Timerrrs/TimerQueue.hpp"
#include <condition_variable>
#include <mutex>
#include <vvv/list.hpp>

namespace renn::rt {

class RunLoop : public IExecutor, public timers::TScheduler {
  public:
    RunLoop() = default;

    RunLoop(const RunLoop&) = delete;
    RunLoop& operator=(const RunLoop&) = delete;
    RunLoop(RunLoop&&) = delete;
    RunLoop& operator=(RunLoop&&) = delete;

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

}  // namespace renn::rt
