#include <gtest/gtest.h>

#include "../src/LazyFuture/FF/Get.hpp"
#include "../src/LazyFuture/FF/Ready.hpp"

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
