#pragma once

#include <cassert>
#include <condition_variable>
#include <cstddef>
#include <mutex>

namespace renn::sync {

class WaitGroup {
  private:
    /* +---+---+---+---+---+---+---+---+ */

    std::mutex mtx_;
    std::condition_variable all_done_;
    size_t count_{0};

    /* +---+---+---+---+---+---+---+---+ */

  public:
    void add(size_t count = 1);

    void done();

    void wait();
};


};  // namespace renn::sync
