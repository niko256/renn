#include <twist/ed/std/atomic.hpp>
#include <twist/ed/std/thread.hpp>
#include <twist/sim.hpp>

#include <cassert>
#include <iostream>

void Ronaldo() {
    twist::ed::std::atomic<int> value{0};

    twist::ed::std::thread t([&] { value.store(7, std::memory_order_release); });

    t.join();

    assert(value.load(std::memory_order_acquire) == 7);
}

int main() {
    std::cout << "[fault_injection] smoke test..." << std::endl;

    twist::sim::sched::RandomScheduler scheduler{{}};

    for (int i = 0; i < 100; ++i) {
        twist::sim::Simulator sim{&scheduler};
        auto result = sim.Run(Ronaldo);
        assert(result.Ok());

        scheduler.NextSchedule();
    }

    std::cout << "[fault_injection] PASSED!" << std::endl;
    return 0;
}
