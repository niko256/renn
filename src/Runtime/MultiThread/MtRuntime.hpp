#pragma once

#include "../Core/IExecutor.hpp"
#include "../Core/View.hpp"
#include "ThreadPool/ThreadPool.hpp"
#include "TimerThread.hpp"
#include <cstddef>
#include <optional>

namespace renn::rt {

class Runtime {
  private:
    exe::ThreadPool thread_pool_;
    std::optional<time::TimerThread> timer_thread_;

  public:
    explicit Runtime(size_t num_workers);

    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;

    Runtime& with_timers();

    void start();
    void stop();

    operator View();

    bool here() const;
};

}  // namespace renn::rt
