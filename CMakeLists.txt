cmake_minimum_required(VERSION 3.3)
project(platform)
SET(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -Wall -std=c++14 -fPIC -pthread")

# 编译
if(COMPILE_MODE MATCHES "TEST")
    add_subdirectory(src/test)
else()
    add_subdirectory(src/core)
endif()
