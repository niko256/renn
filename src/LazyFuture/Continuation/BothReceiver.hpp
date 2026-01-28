#pragma once

#include "../Core/Role.hpp"
#include "Continuation.hpp"
#include "../../Runtime/Core/State.hpp"
#include <optional>
#include <atomic>
#include <tuple>

namespace renn::future::cont {

/* synchronizes two parallel futures */

/* Waits for both to complete, then forwards pair to downstream */
template <typename L, typename R, typename Downstream>
struct BothReceiver {
    using ResultType = std::tuple<L, R>;

    Downstream downstream_;
    std::optional<L> left_;
    std::optional<R> right_;
    std::atomic<int> count_{0};
    rt::State state_;

    BothReceiver(Downstream d)
        : downstream_(std::move(d)),
          left_(std::nullopt),
          right_(std::nullopt) {}

    /* Non-movable */
    BothReceiver(BothReceiver&&) = delete;
    BothReceiver(const BothReceiver&) = delete;

    void try_complete() {
        if (count_.load() == 2) {
            downstream_.proceed(
                std::make_tuple(std::move(*left_), std::move(*right_)), state_
            );
        }
    }

    struct LeftCont : role::ContinuationTag {
        BothReceiver* self_;

        LeftCont(BothReceiver* s)
            : self_(s) {}

        void proceed(L value, rt::State state) {
            self_->left_.emplace(std::move(value));
            self_->state_ = state;
            self_->count_.fetch_add(1);
            self_->try_complete();
        }
    };

    struct RightCont : role::ContinuationTag {
        BothReceiver* self_;

        RightCont(BothReceiver* s)
            : self_(s) {}

        void proceed(R value, rt::State state) {
            self_->right_.emplace(std::move(value));
            self_->state_ = state;
            self_->count_.fetch_add(1);
            self_->try_complete();
        }
    };
};

}  // namespace renn::future::cont
