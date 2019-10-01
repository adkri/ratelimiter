#include <strategy/SlidingWindowLogStrategy.hpp>

namespace ratelimiter {

SlidingWindowLogStrategy::SlidingWindowLogStrategy(
    int64_t maxRequestPerSecond) {
  maxRequestPerSec = maxRequestPerSecond;

  // TODO: clean up the log after sometime since it is unbounded
  // make a reaper to do this -- maybe?
}

bool SlidingWindowLogStrategy::allow() {
  std::lock_guard<std::mutex> lock(logMutex);
  std::chrono::milliseconds currentTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  long boundary = currentTime.count() - 1000;
  while (!log.empty() && log.front() <= boundary) {
    log.pop();
  }
  log.emplace(currentTime.count());
  return log.size() <= maxRequestPerSec;
}

}  // namespace ratelimiter