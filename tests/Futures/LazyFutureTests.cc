#include <cmath>
#include <gtest/gtest.h>

#include "../../src/LazyFuture/FF/Get.hpp"
#include "../../src/LazyFuture/FF/Map.hpp"
#include "../../src/LazyFuture/FF/Ready.hpp"
#include "../../src/LazyFuture/FF/Pure.hpp"
#include "../../src/LazyFuture/FF/Via.hpp"
#include "Core/View.hpp"
#include "ThreadPool/ThreadPool.hpp"

using namespace renn;

class LFTest : public ::testing::Test {};

TEST_F(LFTest, ReadyInt) {
    auto f = future::Ready(88);
    int res = future::Get(std::move(f));
    EXPECT_EQ(res, 88);
}

TEST_F(LFTest, ReadyStr) {
    auto f = future::Ready(std::string("Halo!"));
    std::string result = future::Get(std::move(f));
    EXPECT_EQ(result, "Halo!");
}

TEST_F(LFTest, MapSimple) {
    auto f = future::Value(888)
             | future::Map([](int input) { return input += (56 * 2); });

    int res = future::Get(std::move(f));

    EXPECT_EQ(res, 1000);
}

TEST_F(LFTest, MapChain) {
    auto f1 = future::Value(1);
    auto f2 = std::move(f1) | future::Map([](int x) { return x + 1; });
    auto f3 = std::move(f2) | future::Map([](int x) { return x * 2; });
    auto f4 = std::move(f3) | future::Map([](int x) { return x + 10; });

    int res = future::Get(std::move(f4));
    EXPECT_EQ(res, 14);  // ((1 + 1) * 2) + 10
}

TEST_F(LFTest, Just) {
    exe::ThreadPool dumb_rt{4};
    dumb_rt.start();

    auto f = future::Pure() | future::Via(dumb_rt)
             | future::Map([](future::Unit) { return 8; });

    int res = future::Get(std::move(f));

    EXPECT_EQ(res, 8);

    dumb_rt.stop();
}
