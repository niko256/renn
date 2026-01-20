#pragma once

#include "../Core/IExecutor.hpp"
#include "../Timerrrs/TScheduler.hpp"
#include "../Timerrrs/TimerQueue.hpp"
#include <thread>

namespace renn::timers {

class TimerThread : public TScheduler {
  public:
    explicit TimerThread(rt::IExecutor* executor);

    /* timer::IScheduler */
    void set(Duration delay, TimerBase* timer) override;

    void start();
    void stop();

  private:
    void run_loop();

  private:
    rt::IExecutor* executor_;
    timers::TimerBlockingQueue timers_;
    std::thread thread_;
};

}  // namespace renn::timers
