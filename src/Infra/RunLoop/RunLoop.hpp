#pragma once

#include "../Core/Env.hpp"
#include "../Time/ITimerService.hpp"
#include "Infra/Time/TimerQueue.hpp"
#include "../../Utils/StdLike.hpp"
#include <ntrusive/intrusive.hpp>

namespace renn::rt {

class RunLoop : public IExecutor, public time::ITimerService {
  private:
    /* +---+---+---+---+---+---+---+---+---+ */

    IntrusiveList<TaskBase> tasks_;
    time::TimerQueue timers_;

    stdlike::mutex mtx_;
    stdlike::condition_variable condvar_;

    bool stop_requested_{false};

    /* +---+---+---+---+---+---+---+---+---+ */

  public:
    RunLoop() = default;

    RunLoop(const RunLoop&) = delete;
    RunLoop& operator=(const RunLoop&) = delete;
    RunLoop(RunLoop&&) = delete;
    RunLoop& operator=(RunLoop&&) = delete;

    auto env() -> Env;
    operator Env();

    void submit(TaskBase* task) override;

    void run();

    void stop();

    void set(time::Duration delay, time::TimerBase* timer) override;

    bool has_work(time::Timepoint now) const;
};

}  // namespace renn::rt
