#include <gtest/gtest.h>
#include <strategy/FixedWindowCounterStrategy.hpp>
#include <chrono>
#include <memory>
#include <thread>

struct FixedWindowCounterStrategyTest : public ::testing::Test {
  int64_t maxRequestPerSecond = 2;
  std::unique_ptr<ratelimiter::FixedWindowCounterStrategy> tbs;
  virtual void SetUp() override {
    tbs =
        std::make_unique<ratelimiter::FixedWindowCounterStrategy>(maxRequestPerSecond);
  }

  virtual void TearDown() override {}
};

TEST_F(FixedWindowCounterStrategyTest, CHECKCOUNTER) {
  // TODO: write more explicit tests here on a fixed counter
  EXPECT_EQ(true, tbs->allow());
  EXPECT_EQ(true, tbs->allow());

  EXPECT_EQ(false, tbs->allow());
  
  // now wait 1 second to refill the tokens
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_EQ(true, tbs->allow());
}
