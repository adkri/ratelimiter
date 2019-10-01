#include <strategy/TokenBucketStrategy.hpp>

namespace ratelimiter {

TokenBucketStrategy::TokenBucketStrategy(int maxRequestPerSecond) {
  maxRequestPerSec = maxRequestPerSecond;
  tokens = maxRequestPerSec;

  refillerThread = std::thread([this]() {
    while (running_) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      refillTokens(maxRequestPerSec);
    };
  });
}

TokenBucketStrategy::~TokenBucketStrategy() {
  running_ = false;
  refillerThread.join();
}

bool TokenBucketStrategy::allow() {
  std::lock_guard<std::mutex> lock(tokenMutex);
  if (tokens == 0) {
    return false;
  }
  tokens--;
  return true;
}

void TokenBucketStrategy::refillTokens(int count) {
  std::lock_guard<std::mutex> lock(tokenMutex);
  tokens = std::min(tokens + count, maxRequestPerSec);
}

}  // namespace ratelimiter