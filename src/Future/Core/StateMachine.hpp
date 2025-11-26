#pragma once

#include <atomic>
#include <cstdint>

class StateMachine {
  public:
    bool consume();

    bool produce();

  private:
    enum States : uint64_t {
        Init = 0,
        Producer = 1,
        Consumer = 2,
        Rendezvouz = Producer | Consumer,
    };

    std::atomic<States> state_{States::Init};
};

/* ///////////////////////////////////////////////////////////// */

bool StateMachine::consume() {
    return state_.fetch_or(States::Consumer) == States::Producer;
}

bool StateMachine::produce() {
    return state_.fetch_or(States::Producer) == States::Consumer;
}
