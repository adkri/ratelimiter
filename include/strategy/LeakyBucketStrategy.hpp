#pragma once
#include <chrono>
#include <mutex>

namespace ratelimiter {

class LeakyBucketStrategy {
 public:
  LeakyBucketStrategy(int maxRequestPerSec);
  bool allow();

 private:
  std::chrono::milliseconds nextAllowedTime;
  std::chrono::milliseconds kRequestIntervalMillis;
  std::mutex bucketMutex;
};

}  // namespace ratelimiter