#include "WaitGroup.hpp"

//////////////////////////////////////////////////////////////////////

namespace renn::sync {

void WaitGroup::add(size_t count) {
    std::unique_lock<std::mutex> lock(mtx_);
    count_ += count;
}

void WaitGroup::done() {
    std::unique_lock<std::mutex> lock(mtx_);

    assert(count_ > 0);
    --count_;

    if (count_ == 0) {
        all_done_.notify_all();
    }
}

void WaitGroup::wait() {
    std::unique_lock<std::mutex> lock(mtx_);
    all_done_.wait(lock, [this] {
        return count_ == 0;
    });
}

};  // namespace renn::sync
