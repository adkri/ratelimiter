#pragma once
#include <atomic>
#include <chrono>
#include <memory>
#include <unordered_map>

using atomic_ptr_t = std::shared_ptr<std::atomic<int64_t>>;
typedef std::unordered_map<int64_t, atomic_ptr_t> atomic_value_map_t;
namespace ratelimiter {

class SlidingWindowStrategy {
 public:
  SlidingWindowStrategy(int64_t maxRequestPerSecond);
  bool allow();

 private:
  int64_t maxRequestPerSec;

  atomic_value_map_t window;
};
}  // namespace ratelimiter