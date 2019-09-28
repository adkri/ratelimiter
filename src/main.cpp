#include <Counter.hpp>
#include <iostream>

int main() {
  Counter c;
  c.incrementCounter();
  c.incrementCounter();
  std::cout << c.getCount();
  return 0;
}