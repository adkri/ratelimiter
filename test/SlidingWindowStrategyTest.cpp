#include <gtest/gtest.h>
#include <strategy/SlidingWindowStrategy.hpp>
#include <chrono>
#include <memory>
#include <thread>

struct SlidingWindowStrategyTest : public ::testing::Test {
  int64_t maxRequestPerSecond = 2;
  std::unique_ptr<ratelimiter::SlidingWindowStrategy> tbs;
  virtual void SetUp() override {
    tbs =
        std::make_unique<ratelimiter::SlidingWindowStrategy>(maxRequestPerSecond);
  }

  virtual void TearDown() override {}
};

TEST_F(SlidingWindowStrategyTest, CHECKCOUNTER) {
  // TODO: write more explicit tests here on a fixed counter
  EXPECT_EQ(true, tbs->allow());
  EXPECT_EQ(true, tbs->allow());

  EXPECT_EQ(false, tbs->allow());
  
  // now wait 1 second to refill the tokens
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_EQ(true, tbs->allow());
}
