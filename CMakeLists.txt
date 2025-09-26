cmake_minimum_required(VERSION 3.26)
project(MyTasks)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyTasks
        YA2014/play_with_array_brute_force.cpp)
        #Tinkoff/5.cpp)
        #Experiments/experiment4.cpp)

add_subdirectory(FuzzExperiment)