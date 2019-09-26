#include<iostream>
#include<Counter.hpp>

int main() {
    Counter c;
    c.incrementCounter();
    c.incrementCounter();
    std::cout << c.getCount();
    return 0;
}