#pragma once

#include "../Core/IExecutor.hpp"
#include "../Timerrrs/TScheduler.hpp"
#include "../Timerrrs/TimerQueue.hpp"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace renn::timers {

class TimerThread : public TScheduler {
  public:
    explicit TimerThread(rt::IExecutor* executor);

    void set(Duration delay, TimerBase* timer) override;

    void start();
    void stop();

  private:
    void run_loop();

  private:
    rt::IExecutor* executor_;
    IntrusiveTimerQueue timers_;
    std::thread thread_;

    std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> stopped_{false};
};

}  // namespace renn::timers
