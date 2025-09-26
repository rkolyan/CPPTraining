cmake_minimum_required(VERSION 3.19)
project(first_fuzz_project)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)

add_executable(FuzzTest play_with_array_test_functions.cpp test_play_with_array.cpp)