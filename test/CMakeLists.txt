cmake_minimum_required(VERSION 3.15)

set(SOURCES
    CounterTest.cpp
)

add_executable(ratelimiter_test ${SOURCES})
target_link_libraries(ratelimiter_test PUBLIC
    gtest_main
    core
)

add_test(
    NAME ratelimiter_test
    COMMAND ratelimiter_test
)