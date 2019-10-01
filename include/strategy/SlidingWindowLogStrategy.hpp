#pragma once
#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <queue>

namespace ratelimiter {

class SlidingWindowLogStrategy {
 public:
  SlidingWindowLogStrategy(int64_t maxRequestPerSecond);
  bool allow();

 private:
  int64_t maxRequestPerSec;
  std::mutex logMutex;
  std::queue<long> log;
};
}  // namespace ratelimiter