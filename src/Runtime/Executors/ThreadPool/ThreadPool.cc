#include "ThreadPool.hpp"
#include <thread>

namespace renn::exe {

ThreadPool::ThreadPool(size_t num_threads)
    : num_threads_(
          num_threads > 0 ? num_threads : std::thread::hardware_concurrency()
      ) {}

/// [condition]: destructor must be called after close()
ThreadPool::~ThreadPool() {
    assert(stopped_ && "ThreadPool must be stopped before the destructioon");
}

/// Starts the worker threads
/// this method can be called only once
void ThreadPool::start() {
    assert(!stopped_);

    workers_.reserve(num_threads_);

    for (size_t i = 0; i < num_threads_; ++i) {
        workers_.emplace_back([this] { worker_loop(); });
    }
}

/// submits renns for execution
/// [condition] : it must be called after start() and before stop()
void ThreadPool::submit(RennBase* procedure) {
    // just ensure here that user follows the pool's lifecycle 'contract'
    assert(!stopped_);

    if (!procedure) {
        return;
    }

    renns_.push(std::move(procedure));
}

/// Stops the pool [waits for all worker threads to finish]
/// => no new renns will be submitted
/// ![must be called only once]!
void ThreadPool::stop() {
    // another ensuring that user follow stop rules
    assert(!stopped_);

    stopped_.store(true);

    // closing the queue is th signal to worker threads to stop working for new
    // renns and exit their loop
    renns_.close();

    // waits for all worker threads to complete their execution
    // [bc when stop() returns, all thread resources must be released]
    for (auto& w : workers_) {
        if (w.joinable()) {
            w.join();
        }
    }
}

/// Get a pointer to the ThreadPool instance for the current thread
ThreadPool* ThreadPool::current() {
    return current_pool_;
}

/// Main loop for each worker-thread
/// [every worker continuously pulls renns from the queue and exec them, 'till
/// queue is empty and closed]
void ThreadPool::worker_loop() {
    current_pool_ = this;

    while (true) {
        // pops blocks untill renn is available OR the queue is closed
        RennBase* renn = renns_.pop();

        if (!renn) {
            // the worker's job is done
            break;
        }

        try {
            // executing the renn
            renn->run();
        } catch (...) {
            // if a submitted renn throws an exception that is doesn't handle
            // internally, we catch it here
            //
            // !!! : A renn that allows an exception to escape is violating its
            // contract
            // !!! and has likely left application in a corrupted, unknowm state
            // [broken invariants etc..]
            // !!! The ThreadPool's responsibility is to execute renns, not to
            // reason about their internal logic or error handling
            // !!! Thus continuing execution would be unsafe => the only
            // responsible action is to terminate entire program to prevent
            // further damage

            std::terminate();
        }
    }
}
};  // namespace renn::exe
