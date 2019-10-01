#include <gtest/gtest.h>
#include <strategy/LeakyBucketStrategy.hpp>
#include <chrono>
#include <memory>
#include <thread>

struct LeakyBucketStrategyTest : public ::testing::Test {
  int maxRequestPerSecond = 2;
  std::unique_ptr<ratelimiter::LeakyBucketStrategy> lbs;
  virtual void SetUp() override {
    lbs =
        std::make_unique<ratelimiter::LeakyBucketStrategy>(maxRequestPerSecond);
  }

  virtual void TearDown() override {}
};

TEST_F(LeakyBucketStrategyTest, CHECKCOUNTER) {
  EXPECT_EQ(true, lbs->allow());
  // now the nextAllowed time is currentTime + (1000/maxRequestSecond) i.e
  // +500ms
  EXPECT_EQ(false, lbs->allow());

  // so we wait for 500ms more
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  EXPECT_EQ(true, lbs->allow());
}
