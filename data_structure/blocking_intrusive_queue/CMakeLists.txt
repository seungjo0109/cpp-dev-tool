cmake_minimum_required(VERSION 3.2)
project(blocking_intrusive_queue)

set(CMAKE_C_FLAGS -pthread)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(${PROJECT_NAME}
    test_blocking_intrusive_queue.cc
)