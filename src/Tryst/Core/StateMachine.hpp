#pragma once

#include <atomic>
#include <cstdint>

class StateMachine {
  public:
    bool consume();

    bool produce();

  private:
    enum States : uint64_t {
        INIT = 0,
        PRODUCER = 1,
        CONSUMER = 2,
        TRYST = PRODUCER | CONSUMER,
    };

    std::atomic<uint64_t> state_{States::INIT};
};

/* ///////////////////////////////////////////////////////////// */

inline bool StateMachine::consume() {
    return state_.fetch_or(States::CONSUMER) == States::PRODUCER;
}

inline bool StateMachine::produce() {
    return state_.fetch_or(States::PRODUCER) == States::CONSUMER;
}
