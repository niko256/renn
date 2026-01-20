#include "../src/Runtime/Executors/ThreadPool/ThreadPool.hpp"
#include "../src/Sync/WaitGroup/WaitGroup.hpp"

#include "../src/Fiber/Core/Fiber.hpp"
#include "../src/Fiber/ExeCtrl/Go.hpp"
#include <arpa/inet.h>
#include <format>
#include <gtest/gtest.h>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace renn;

using Scheduler = exe::ThreadPool;
using WaitGroup = renn::sync::WaitGroup;

class FiberTest : public ::testing::Test {
  protected:
    std::unique_ptr<Scheduler> sched_;

    void SetUp() override {
        sched_ = std::make_unique<Scheduler>(8);
        sched_->start();
    }

    void TearDown() override {
        sched_->stop();
    }
};

TEST_F(FiberTest, SimpleExecution) {
    WaitGroup wg;
    wg.add(1);

    fiber::go(*sched_, [&wg] {
        // fmt::print("Here we go...");
        wg.done();
    });

    wg.wait();
}

TEST_F(FiberTest, AfewSteps) {
    WaitGroup wg;
    constexpr int kFibersCount = 29;


    wg.add(kFibersCount);

    for (int i = 0; i < kFibersCount; ++i) {
        fiber::go(*sched_, [&wg, i] {
            std::cout << std::format("Fiber {} completed", i) << std::endl;
            wg.done();
        });
    }

    wg.wait();
}

TEST_F(FiberTest, ConcurrentFileIO) {
}

TEST_F(FiberTest, ExceptionInFiber) {
}

TEST_F(FiberTest, TheHordeOfFibers) {
}

TEST_F(FiberTest, Rescheduling1) {
}

TEST_F(FiberTest, Rescheduling2) {
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
