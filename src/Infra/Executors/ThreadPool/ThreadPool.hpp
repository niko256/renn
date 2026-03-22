#pragma once

#include "../../Core/IExecutor.hpp"
#include "../../Core/Task.hpp"
#include "IntrusiveQueue.hpp"
#include "../Utils/StdLike.hpp"
#include <cassert>
#include <cstddef>
#include <thread>
#include <vector>

namespace renn::exe {

class ThreadPool : public rt::IExecutor {
  private:
    /* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

    UnboundedBlockingQueue<TaskBase> tasks_;
    const size_t num_threads_;
    std::vector<std::thread> workers_;

    stdlike::atomic<bool> stopped_{false};

    // A thread-local pointer to the current ThreadPool instance
    inline static thread_local ThreadPool* current_pool_ = nullptr;

    /* +---+---+---+---+---+---+---+---+---+---+---+---+---+---+ */

  public:
    explicit ThreadPool(size_t num_threads);

    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) noexcept = delete;

    void start();

    void stop();

    static ThreadPool* current();

    void submit(TaskBase* procedure) override;

  private:
    void worker_loop();
};

};  // namespace renn::exe
