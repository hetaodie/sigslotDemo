cmake_minimum_required(VERSION 3.15)
project(sigslotDemo)

set(CMAKE_CXX_STANDARD 11)

include_directories(./src)

add_executable(sigslotDemo main.cpp src/sigslot.cc src/sigslot.h)