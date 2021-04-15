#include <Counter.hpp>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <strategy/FixedWindowCounterStrategy.hpp>
#include <strategy/LeakyBucketStrategy.hpp>
#include <strategy/SlidingWindowLogStrategy.hpp>
#include <strategy/SlidingWindowStrategy.hpp>
#include <strategy/TokenBucketLazyRefillStrategy.hpp>
#include <strategy/TokenBucketStrategy.hpp>
#include <thread>
#include <vector>

template <typename T>
void sendRequest(T ratelimiter, int totalCount, int requestPerSec) {
  auto startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());

  std::vector<std::thread*> ts;

  std::condition_variable cv;
  std::mutex countDownLock;
  uint32_t count = totalCount;

  for (int i = 0; i < totalCount; i++) {
    std::thread* t = new std::thread([&]() {
      while (!ratelimiter->allow()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      std::unique_lock<std::mutex> lck(countDownLock);
      --count;
      if (count <= 0) {
        cv.notify_all();
      }
    });
    ts.push_back(t);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(1000 / requestPerSec));
  }

  {
    if (count > 0) {
      std::unique_lock<std::mutex> lck(countDownLock);
      cv.wait(lck);
    }
  }

  int i = 0;
  while (i < ts.size()) {
    ts[i++]->join();
  }
  auto endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch());
  double duration = (endTime.count() - startTime.count()) / 1000.0;
  std::cout << totalCount << " requests processed in " << duration
            << " seconds." << std::endl;
  std::cout << "Rate: " << (double)totalCount / duration << " per second"
            << std::endl;
}

template <typename T>
void startRequestThread(T ratelimiter) {
  std::thread([&]() {
    sendRequest(ratelimiter, 10, 1);
    sendRequest(ratelimiter, 20, 2);
    sendRequest(ratelimiter, 50, 5);
    sendRequest(ratelimiter, 100, 10);
    sendRequest(ratelimiter, 200, 20);
    sendRequest(ratelimiter, 250, 25);
    sendRequest(ratelimiter, 500, 50);
    sendRequest(ratelimiter, 1000, 100);
  }).join();
}

int main() {
  const int MAX_REQUESTS_PER_SEC = 10;
  // std::shared_ptr<ratelimiter::LeakyBucketStrategy> lbs =
  //     std::make_shared<ratelimiter::LeakyBucketStrategy>(100);

  std::shared_ptr<ratelimiter::TokenBucketStrategy> lbs =
      std::make_shared<ratelimiter::TokenBucketStrategy>(MAX_REQUESTS_PER_SEC);

  // std::shared_ptr<ratelimiter::TokenBucketLazyRefillStrategy> lbs =
  //     std::make_shared<ratelimiter::TokenBucketLazyRefillStrategy>(MAX_REQUESTS_PER_SEC);

  // std::shared_ptr<ratelimiter::FixedWindowBucketStrategy> lbs =
  //     std::make_shared<ratelimiter::FixedWindowBucketStrategy>(MAX_REQUESTS_PER_SEC);

  /* The following two rate limiter will never end if request rate exceeds the
   * limit */
  // std::shared_ptr<ratelimiter::SlidingWindowStrategy> lbs =
  //     std::make_shared<ratelimiter::SlidingWindowStrategy>(MAX_REQUESTS_PER_SEC);

  // std::shared_ptr<ratelimiter::SlidingWindowLogStrategy> lbs =
  //     std::make_shared<ratelimiter::SlidingWindowLogStrategy>(MAX_REQUESTS_PER_SEC);

  startRequestThread(lbs);
  Counter c;
  c.incrementCounter();
  c.incrementCounter();
  std::cout << c.getCount();
  return 0;
}
