#include <strategy/TokenBucketLazyRefillStrategy.hpp>

namespace ratelimiter {

TokenBucketLazyRefillStrategy::TokenBucketLazyRefillStrategy(
    int maxRequestPerSecond) {
  maxRequestPerSec = maxRequestPerSecond;
  tokens = maxRequestPerSec;
  lastRefillTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
}

bool TokenBucketLazyRefillStrategy::allow() {
  std::lock_guard<std::mutex> lock(tokenMutex);
  refillTokens();
  if (tokens == 0) {
    return false;
  }
  tokens--;
  return true;
}

/**
 * Refill Tokens
 * (current time - last refill time) * max allowed tokens per time unit
 */
void TokenBucketLazyRefillStrategy::refillTokens() {
  std::chrono::milliseconds currentTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  double secondsSinceLastRefill =
      (currentTime.count() - lastRefillTime.count()) / 1000.0;
  int count = (int)(secondsSinceLastRefill * maxRequestPerSec);
  if (count > 0) {
    tokens = std::min(tokens + count, maxRequestPerSec);
    lastRefillTime = currentTime;
  }
}

}  // namespace ratelimiter