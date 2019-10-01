cmake_minimum_required(VERSION 3.15)
project(ratelimiter)


# find a boost install with the libraries filesystem and system
find_package(Boost 1.71.0 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})
#check if boost was found
if(Boost_FOUND)
  message("boost found")
else()
  message(FATAL_ERROR "cannot find boost")
endif()

# Configure
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release ... FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# enable testing with googletest
enable_testing()
add_subdirectory(googletest)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("INFO: Debug build")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message("INFO: Release build")
elseif()
  message("WARNING: Unknown build type")
endif()

# set the headers
set(HEADERS
  include/Counter.hpp
  include/strategy/LeakyBucketStrategy.hpp
  include/strategy/TokenBucketStrategy.hpp
  include/strategy/TokenBucketLazyRefillStrategy.hpp
  include/strategy/FixedWindowCounterStrategy.hpp
  include/strategy/SlidingWindowLogStrategy.hpp
  include/strategy/SlidingWindowStrategy.hpp
)

# set the sources
set(SOURCES
  src/Counter.cpp
  src/strategy/LeakyBucketStrategy.cpp
  src/strategy/TokenBucketStrategy.cpp
  src/strategy/TokenBucketLazyRefillStrategy.cpp
  src/strategy/FixedWindowCounterStrategy.cpp
  src/strategy/SlidingWindowLogStrategy.cpp
  src/strategy/SlidingWindowStrategy.cpp
)
# Add library
add_library(core ${HEADERS} ${SOURCES})

# Include directories
target_include_directories(core
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include)

# Make executable
add_executable(ratelimiter
  src/main.cpp
)

# Link libraries
target_link_libraries(ratelimiter PRIVATE
  core
  ${Boost_LIBRARIES}
)

# add the test subdirectory
add_subdirectory(test)
