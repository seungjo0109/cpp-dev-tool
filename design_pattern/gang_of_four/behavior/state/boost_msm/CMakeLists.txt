cmake_minimum_required(VERSION 3.5)
project(boost_msm_state_machine)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(Boost REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIR}
)

add_executable(boost_msm_state_machine
    boost_msm_state_machine.cc
)
target_link_libraries(boost_msm_state_machine
    ${Boost_LIBS}
)