#pragma once
#include <chrono>
#include <mutex>
#include <thread>

namespace ratelimiter {

class TokenBucketLazyRefillStrategy {
 public:
  TokenBucketLazyRefillStrategy(int maxRequestPerSec);
  bool allow();

 private:
  void refillTokens();
  int tokens;
  int maxRequestPerSec;
  std::chrono::milliseconds lastRefillTime;
  std::mutex tokenMutex;
};

}  // namespace ratelimiter