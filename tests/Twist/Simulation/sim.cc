#include <twist/ed/std/thread.hpp>
#include <twist/ed/std/atomic.hpp>
#include <twist/sim.hpp>
#include <cassert>
#include <iostream>

void FirstStupidSimulation() {
    twist::ed::std::atomic<int> ankara_messiiiiii{10};

    twist::ed::std::thread t1([&] {
        ankara_messiiiiii.fetch_add(1, std::memory_order_relaxed);
    });

    twist::ed::std::thread t2([&] {
        ankara_messiiiiii.fetch_add(1, std::memory_order_relaxed);
    });

    t1.join();
    t2.join();

    assert(ankara_messiiiiii.load() == 12);
}

int main() {
    std::cout << "[simulation] Random scheduler..." << std::endl;

    twist::sim::sched::RandomScheduler scheduler{{}};

    for (int i = 0; i < 100; ++i) {
        twist::sim::Simulator sim{&scheduler};
        auto result = sim.Run(FirstStupidSimulation);
        assert(result.Ok());

        scheduler.NextSchedule();
    }

    std::cout << "[simulation] DFS scheduler..." << std::endl;

    twist::sim::sched::DfsScheduler dfs{{}};

    do {
        twist::sim::Simulator sim{&dfs};
        auto result = sim.Run(FirstStupidSimulation);
        assert(result.Ok());
    } while (dfs.NextSchedule());

    std::cout << "[simulation] PASSED!" << std::endl;
    return 0;
}
