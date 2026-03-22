#pragma once

#include <cassert>
#include "../../Utils/StdLike.hpp"
#include <cstddef>

namespace renn::sync {

class WaitGroup {
  private:
    /* +---+---+---+---+---+---+---+---+ */

    stdlike::mutex mtx_;
    stdlike::condition_variable all_done_;
    size_t count_{0};

    /* +---+---+---+---+---+---+---+---+ */

  public:
    void add(size_t count = 1);

    void done();

    void wait();
};


};  // namespace renn::sync
