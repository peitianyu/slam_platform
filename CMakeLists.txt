# 指定cmake版本
cmake_minimum_required(VERSION 3.3)
# 工程名
project(platform)

#cmake的c++设置
# 告知當前使用的是交叉編譯方式，必須配置
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
# 执行路径设置
# SET(EXECUTABLE_OUTPUT_PATH ../bin)
# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -std=c++14 -fPIC -g -pthread")

file(GLOB_RECURSE ALL_LIBRIRY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cc)

# 添加.h文件
include_directories(src/common)

# 执行文件
add_executable(publish src/publish.cc ${ALL_LIBRIRY_SRCS})
target_link_libraries(publish rt)

# 执行文件
add_executable(subscribe src/subscribe.cc ${ALL_LIBRIRY_SRCS})
target_link_libraries(subscribe rt)
