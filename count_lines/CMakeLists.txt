cmake_minimum_required(VERSION 3.15)
project(count_lines)

set(CMAKE_CXX_STANDARD 14)

add_executable(count_lines main.cpp)

target_link_libraries(count_lines
        opencv)