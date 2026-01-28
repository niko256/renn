#pragma once

#include "../../Core/IExecutor.hpp"
#include "../../Core/Renn.hpp"
#include "IntrusiveQueue.hpp"
#include <atomic>
#include <cassert>
#include <cstddef>
#include <thread>
#include <vector>

namespace renn::exe {

class ThreadPool : public rt::IExecutor {
  public:
    explicit ThreadPool(size_t num_threads);

    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) noexcept = delete;

    void start();

    void stop();

    static ThreadPool* current();

    void submit(RennBase* procedure) override;

  private:
    void worker_loop();

  private:
    UnboundedBlockingQueue<RennBase> renns_;
    const size_t num_threads_;
    std::vector<std::thread> workers_;

    std::atomic<bool> stopped_{false};


    // A thread-local pointer to the current ThreadPool instance
    inline static thread_local ThreadPool* current_pool_ = nullptr;
};

};  // namespace renn::exe
