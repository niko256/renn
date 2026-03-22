#pragma once

#include "../Core/IExecutor.hpp"
#include "Time/ITimerService.hpp"
#include "Time/TimerQueue.hpp"
#include "../Utils/StdLike.hpp"

namespace renn::time {

class TimerThread : public ITimerService {
  private:
    /* +---+---+---+---+---+---+---+---+---+ */

    rt::IExecutor* executor_;
    time::TimerQueue timers_;
    stdlike::thread thread_;

    stdlike::mutex mtx_;
    stdlike::condition_variable cv_;
    stdlike::atomic<bool> stopped_{false};

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
