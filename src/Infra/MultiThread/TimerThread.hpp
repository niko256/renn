#pragma once

#include "../Core/IExecutor.hpp"
#include "Time/ITimerService.hpp"
#include "Time/TimerQueue.hpp"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace renn::time {

class TimerThread : public ITimerService {
  private:
    /* +---+---+---+---+---+---+---+---+---+ */

    rt::IExecutor* executor_;
    time::TimerQueue timers_;
    std::thread thread_;

    std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> stopped_{false};

    /* +---+---+---+---+---+---+---+---+---+ */

  public:
    explicit TimerThread(rt::IExecutor* executor);

    void set(Duration delay, TimerBase* timer) override;

    void start();
    void stop();

  private:
    void run_loop();
};

}  // namespace renn::time
