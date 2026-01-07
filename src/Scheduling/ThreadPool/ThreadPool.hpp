#pragma once

#include "../../Utils/Renn.hpp"
#include "../IExecutor.hpp"
#include "Queue.hpp"
#include <atomic>
#include <cassert>
#include <cstddef>
#include <thread>
#include <vector>

namespace renn {

// Renn type represents fundamental unit of work in our threadpool
// as polymorphic wrapper for callable objects
// it can store everything that can act like a function (lambda, functor, ptr to method, classic function)
// it doesn't accept and return any arguments
// MOVABLE

class ThreadPool : public sched::IExecutor {
  public:
    explicit ThreadPool(size_t num_threads);

    ~ThreadPool() override;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) noexcept = delete;

    void start();

    void stop();

    static ThreadPool* current();

    void submit(Renn&& procedure) override;

    /// TODO : [FEATURE] Implement std::future-based version of submit method for renns that return values
    /// [this would allow the pool to handle renns that return values]
    ///
    /// The signature should looks like:
    ///
    /// template <typename Func, typename... Args>
    /// auto submit(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>;

  private:
    void worker_loop();

  private:
    UnboundedBlockingQueue<Renn> renns_;
    const size_t num_threads_;
    std::vector<std::thread> workers_;

    // ensure visibility of state changes accross threads
    // they are atomic to safely sync with submit() method which can be called from any thread
    // !!! : A dedicated mutex isn't require here,
    // !!! : bc we want to fulfill the condition that start() and stop() are called from a single-managing thread
    // !!! : and are not concurrent with each other.
    //
    std::atomic<bool> started_;
    std::atomic<bool> stopped_;

    /// TODO::: to ensure that using two atomic flags is a better choice than using an atomic state
    /// ...alignment to cache-line, bc enum is just 1 byte...??
    ///
    // enum class State {
    //     Idle,     // Initial state
    //     Running,  // State after start()
    //     Stopped,  // State after stop()
    // };
    // std::atomic<State> state_{State::Idle};


    // A thread-local pointer to the current ThreadPool instance
    // each thread gets its own copy of this variable
    inline static thread_local ThreadPool* current_pool_ = nullptr;
};

};  // namespace renn
