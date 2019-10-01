#include <strategy/FixedWindowCounterStrategy.hpp>

namespace ratelimiter {

FixedWindowCounterStrategy::FixedWindowCounterStrategy(
    int64_t maxRequestPerSecond) {
  maxRequestPerSec = maxRequestPerSecond;

  // TODO: clean up the map after sometime to remove stale data
  // make a reaper to do this -- maybe?
}

bool FixedWindowCounterStrategy::allow() {
  std::chrono::milliseconds currentTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  int64_t windowKey = (currentTime.count() / 1000) * 1000;

  atomic_value_map_t::iterator itr = window.find(windowKey);
  if (itr == window.end()) {
    window[windowKey] = atomic_ptr_t(new std::atomic<int64_t>(0));
  }
  atomic_ptr_t ptr = window[windowKey];
  ++*ptr;
  int64_t count = *ptr;
  return count <= maxRequestPerSec;
}

}  // namespace ratelimiter
