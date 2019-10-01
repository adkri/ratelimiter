#pragma once
#include <chrono>
#include <mutex>
#include <thread>

namespace ratelimiter {

class TokenBucketStrategy {
 public:
  TokenBucketStrategy(int maxRequestPerSec);
  ~TokenBucketStrategy();
  bool allow();

 private:
  void refillTokens(int count);
  int tokens;
  int maxRequestPerSec;
  std::thread refillerThread;
  std::mutex tokenMutex;
  bool running_{true};
};

}  // namespace ratelimiter