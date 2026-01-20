#pragma once

#include <condition_variable>
#include <mutex>
#include <vvv/list.hpp>

namespace renn::exe {

template <typename T>
class UnboundedBlockingQueue {
  public:
    UnboundedBlockingQueue() = default;

    UnboundedBlockingQueue(const UnboundedBlockingQueue&) = delete;
    UnboundedBlockingQueue(UnboundedBlockingQueue&&) = delete;
    UnboundedBlockingQueue& operator=(const UnboundedBlockingQueue&) = delete;
    UnboundedBlockingQueue& operator=(UnboundedBlockingQueue&&) = delete;

    // Just basic push (add element to the end of the queue)
    // BUT! Behaviour is undefined if it called after close()
    void push(T* item);


    T* pop();

    // Closes the queue for new additions
    // Wakes up all waiting consumers
    void close();

    bool is_closed() const;

  private:
    vvv::IntrusiveList<T> task_queue_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    bool is_closed_{false};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename T>
void UnboundedBlockingQueue<T>::push(T* item) {
    if (is_closed_)
        return;
    {
        std::unique_lock<std::mutex> lock(mtx_);

        task_queue_.PushBack(std::move(item));
    }

    // Notify one waiting thread that new element is available
    cv_.notify_one();
}

template <typename T>
T* UnboundedBlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx_);

    // Waits until queue is not empty OR it has been closed and no more items will be ever produced
    cv_.wait(lock, [this] {
        return !task_queue_.IsEmpty() || is_closed_;
    });

    // After waking up we have to check the conditions of the queue
    if (task_queue_.IsEmpty() && is_closed_) {
        return nullptr;
    }

    // Otherwise, there must be an item in the queue
    return task_queue_.TryPopFront();
}

template <typename T>
void UnboundedBlockingQueue<T>::close() {
    {
        std::lock_guard<std::mutex> lock(mtx_);

        is_closed_ = true;
    }
    // We must notify all threads that our queue has closed
    // so any thread blocked in the pop() method
    // can wake up, see if the queue is closed and empty, and exit
    cv_.notify_all();
}

template <typename T>
bool UnboundedBlockingQueue<T>::is_closed() const {
    std::lock_guard lock(mtx_);
    return is_closed_;
}

};  // namespace renn::exe
