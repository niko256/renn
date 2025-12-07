#pragma once

#include "../../Utils/Callback.hpp"
#include "../../Utils/Result.hpp"
#include "StateMachine.hpp"
#include <optional>

namespace renn {

template <typename T>
class SharedState {
  public:
    void consume(renn::Callback<T> cb);

    void produce(utils::Result<T> res);

  private:
    void tryst();

  private:
    StateMachine state_machine_;
    std::optional<utils::Result<T>> result_;
    std::optional<Callback<T>> callback_;
};

/* ///////////////////////////////////////////////////////////// */

template <typename T>
void SharedState<T>::consume(renn::Callback<T> cb) {
    callback_.emplace(std::move(cb));

    if (state_machine_.consume()) {
        tryst();
    }
}

template <typename T>
void SharedState<T>::produce(utils::Result<T> res) {
    result_.emplace(std::move(res));

    if (state_machine_.produce()) {
        tryst();
    }
}

template <typename T>
void SharedState<T>::tryst() {
    if (result_) {
        (*callback_)(std::move(result_));
        delete this;
    }
}

};  // namespace renn
