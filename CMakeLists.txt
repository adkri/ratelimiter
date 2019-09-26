CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(ratelimiter)

# Configure
IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Release ... FORCE)
ENDIF()

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  MESSAGE("INFO: Debug build")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  MESSAGE("INFO: Release build")
ELSE()
  MESSAGE("WARNING: Unknown build type")
ENDIF()

# Includes
INCLUDE_DIRECTORIES(include)

# Files
FILE(GLOB CORE    "src/*.cpp")
FILE(GLOB HEADERS "include/*.hpp")
FILE(GLOB CLIENT  "src/main.cpp")
LIST(REMOVE_ITEM CORE "${CMAKE_SOURCE_DIR}/src/main.cpp")

# Targets
ADD_LIBRARY(core ${CORE} ${HEADERS})
ADD_EXECUTABLE(ratelimiter  ${CLIENT} ${HEADERS})

# Link core lib
TARGET_LINK_LIBRARIES(ratelimiter core)