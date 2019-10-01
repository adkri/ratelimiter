#include <strategy/LeakyBucketStrategy.hpp>

namespace ratelimiter {

LeakyBucketStrategy::LeakyBucketStrategy(int maxRequestPerSec) {
  kRequestIntervalMillis = std::chrono::milliseconds(1000 / maxRequestPerSec);
  nextAllowedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
}

/**
 * For the leaky bucket, on each request we check if currentTime is greater than the 
 * next allowed time, if it is we allow the request and add the interval time to currentTime
 * to get the new nextAllowedTime
 * 
 */
bool LeakyBucketStrategy::allow() {
  std::lock_guard<std::mutex> lock(bucketMutex);
  std::chrono::milliseconds currentTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  if (currentTime.count() >= nextAllowedTime.count()) {
    nextAllowedTime = currentTime + kRequestIntervalMillis;
    return true;
  }
  return false;
}

}  // namespace ratelimiter