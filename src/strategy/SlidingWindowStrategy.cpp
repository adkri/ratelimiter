#include <strategy/SlidingWindowStrategy.hpp>

namespace ratelimiter {

SlidingWindowStrategy::SlidingWindowStrategy(int64_t maxRequestPerSecond) {
  maxRequestPerSec = maxRequestPerSecond;

  // TODO: clean up the map after sometime to remove stale data
  // make a reaper thread to do this -- maybe?
}

bool SlidingWindowStrategy::allow() {
  std::chrono::milliseconds currentTime =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch());
  int64_t currWindowKey = (currentTime.count() / 1000) * 1000;

  // put it in the map, if not found
  atomic_value_map_t::iterator currItr = window.find(currWindowKey);
  if (currItr == window.end()) {
    window[currWindowKey] = atomic_ptr_t(new std::atomic<int64_t>(0));
  }
  atomic_ptr_t currWindowCount = window[currWindowKey];

  long prevWindowKey = currWindowKey - 1000;
  atomic_value_map_t::iterator prevItr = window.find(prevWindowKey);
  if (prevItr == window.end()) {
    ++*currWindowCount;
    return *currWindowCount <= maxRequestPerSec;
  }

  atomic_ptr_t prevWindowCount = window[prevWindowKey];
  double preWeight = 1 - (currentTime.count() - currWindowKey) / 1000.0;
  ++*currWindowCount;
  long count = (long)(*prevWindowCount * preWeight + *currWindowCount);
  return count <= maxRequestPerSec;
}

}  // namespace ratelimiter