#include <gtest/gtest.h>
#include <strategy/TokenBucketStrategy.hpp>
#include <chrono>
#include <memory>
#include <thread>

struct TokenBucketStrategyTest : public ::testing::Test {
  int maxRequestPerSecond = 2;
  std::unique_ptr<ratelimiter::TokenBucketStrategy> tbs;
  virtual void SetUp() override {
    tbs =
        std::make_unique<ratelimiter::TokenBucketStrategy>(maxRequestPerSecond);
  }

  virtual void TearDown() override {}
};

TEST_F(TokenBucketStrategyTest, CHECKCOUNTER) {
  EXPECT_EQ(true, tbs->allow());
  EXPECT_EQ(true, tbs->allow());
  
  EXPECT_EQ(false, tbs->allow());
  
  // now wait 1 second to refill the tokens
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_EQ(true, tbs->allow());
}
