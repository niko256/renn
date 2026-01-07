#pragma once

#include "../../Utils/Callback.hpp"
#include "../../Utils/Result.hpp"
#include "Callback.hpp"
#include "StateMachine.hpp"
#include <optional>

namespace renn::tryst {

template <typename T>
class SharedState {
  public:
    void consume(renn::Callback<T> cb);

    void produce(utils::Result<T> res);

  private:
    void tryst();

  private:
    StateMachine state_machine_;

    /* Lazy-initialization */
    std::optional<utils::Result<T>> result_;

    /* Lazy-initialization */
    std::optional<UnpackedCallback<T>> callback_;
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

template <typename T>
void SharedState<T>::consume(UnpackedCallback<T> cb) {
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
    /* [Pre-condition] :
     *  > result is set => producer visited shared state
     *  > callback is set => consumer visited shared state
     */
    if (result_) {
        (*callback_)(std::move(result_));
        delete this;
    }
}

};  // namespace renn::tryst
