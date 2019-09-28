#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>
#include <string>
#include "Counter.hpp"

struct CounterTest : public ::testing::Test {
  virtual void SetUp() override {}

  virtual void TearDown() override {}
};

TEST_F(CounterTest, CHECKCOUNTER) {
  Counter c;
  int count;

  c.incrementCounter();
  count = c.getCount();
  EXPECT_EQ(1, count);

  c.incrementCounter();
  count = c.getCount();
  EXPECT_EQ(2, count);
}

TEST_F(CounterTest, BOOSTTEST) {
  std::string s = "counter";
  std::string s_upper = boost::algorithm::to_upper_copy(s);
  EXPECT_EQ("COUNTER", s_upper);
}