#pragma once

#include <atomic>
#include <cstdint>

namespace renn::tryst {

/**
 * @enum States
 * @brief State flags for the rendezvouz pattern.
 *
 * This enum represents possible states in consumer-producer handshake.
 *
 * => Protocol ensures that either :
 *  > Consumer arrives first, waits for producer
 *  > Producer arrives first, waits for consumer
 *  > Both arrive simultaneously
 */

enum States : uint64_t {
    INIT = 0,
    CONSUMER = 1,
    PRODUCER = 2,
    TRYST = PRODUCER | CONSUMER,
};

/**
 * @class StateMachine
 * @brief Wait-free finite state machine for [producer, consumer] synchronization.
 *
 * [Symmetric] : Producer and consumer has identical arrival logic.
 */
class StateMachine {
  public:
    bool consume();

    bool produce();

  private:
    std::atomic<uint64_t> state_{States::INIT};
};

/* |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-| */

/*
 * fetch_or do atomic rmw:
 *  > reads current value (old_value)
 *  > writes (old_value | new_value)
 *  > returns old_value
 */

/* if old_value == States::PRODUCER => automata switches to States::TRYST
 * Otherwise, States::CONSUMER stored
 */
inline bool StateMachine::consume() {
    return state_.fetch_or(States::CONSUMER) == States::PRODUCER;
}

/* if old_value == States::CONSUMER => automata switches to States::TRYST
 * Otherwise, States::PRODUCER stored
 */
inline bool StateMachine::produce() {
    return state_.fetch_or(States::PRODUCER) == States::CONSUMER;
}

};  // namespace renn::tryst
