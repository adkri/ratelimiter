#pragma once
#include<string>

class Counter {
    std::string name;
    int count = 0;
 public:
    void incrementCounter();
    int getCount();
};
