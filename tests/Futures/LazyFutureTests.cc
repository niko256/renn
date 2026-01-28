#include <gtest/gtest.h>
#include <print>
#include <string>
#include <tuple>
#include "../../src/LazyFuture/FF/Get.hpp"
#include "../../src/LazyFuture/FF/Map.hpp"
#include "../../src/LazyFuture/FF/Ready.hpp"
#include "../../src/LazyFuture/FF/Pure.hpp"
#include "../../src/LazyFuture/FF/Via.hpp"
#include "../../src/Runtime/Core/View.hpp"
#include "LazyFuture/FF/FlatMap.hpp"
#include "LazyFuture/FF/Spawn.hpp"
#include "ThreadPool/ThreadPool.hpp"
#include "LazyFuture/FF/Then.hpp"
#include "LazyFuture/FF/Every.hpp"
#include "LazyFuture/FF/Both.hpp"

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

    auto f = future::Pure() | future::Map([](future::Unit) { return 8; });

    int res = future::Get(std::move(f));

    EXPECT_EQ(res, 8);

    dumb_rt.stop();
}

TEST_F(LFTest, SimpleSpawn) {
    exe::ThreadPool pool{4};

    pool.start();

    auto spawn = future::Spawn(pool, []() { return 88; });

    int res = future::Get(std::move(spawn));

    EXPECT_EQ(res, 88);

    pool.stop();
}

TEST_F(LFTest, SimpleVia) {
    exe::ThreadPool pool{4};
    pool.start();

    auto f = future::Pure() | future::Via(rt::make_view(pool))
             | future::Map([](future::Unit) { return 88; });

    int res = future::Get(std::move(f));

    EXPECT_EQ(res, 88);

    pool.stop();
}

TEST_F(LFTest, FlatMapChain) {
    auto f
        = future::Ready(1)
          | future::FlatMap([](int x) { return future::Value(x + 1); })   // 2
          | future::FlatMap([](int x) { return future::Value(x * 18); })  // 36
          | future::FlatMap([](int x) { return future::Value(x % 4); });  // 0

    auto res = future::Get(std::move(f));
    EXPECT_EQ(res, 0);
}

TEST_F(LFTest, SimpleThen) {
    auto f = future::Value(std::make_tuple(8, 9, 7))
             | future::Then([](int a, int b, int c) { return a + b + c; });

    auto res = future::Get(std::move(f));

    EXPECT_EQ(res, 24);
}

TEST_F(LFTest, Every) {
    auto f = future::Ready(10)
             | future::Every(
                 [](int x) { return x * 2; },
                 [](int x) { return x + 1; },
                 [](int x) { return std::to_string(x); }
             );

    auto [a, b, c] = future::Get(std::move(f));

    EXPECT_EQ(a, 20);
    EXPECT_EQ(b, 11);
    EXPECT_EQ(c, "10");
}

TEST_F(LFTest, EveryWithSideEffects) {
    int counter = 0;

    auto f = future::Ready(5)
             | future::Every(
                 [&](int x) {
                     counter++;
                     return x;
                 },
                 [&](int x) {
                     counter++;
                     return x * 2;
                 }
             );

    auto [a, b] = future::Get(std::move(f));

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, 10);
    EXPECT_EQ(counter, 2);
}

TEST_F(LFTest, Both) {
    auto f = future::Both(future::Ready(1), future::Ready(2));

    auto [a, b] = future::Get(std::move(f));
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
}

TEST_F(LFTest, BothWithSpawn) {
    exe::ThreadPool pool{4};
    pool.start();

    auto f = future::Both(
        future::Spawn(pool, [] { return 10; }),
        future::Spawn(pool, [] { return 20; })
    );

    auto [a, b] = future::Get(std::move(f));
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 20);

    pool.stop();
}
