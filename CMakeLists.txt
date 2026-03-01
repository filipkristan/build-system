cmake_minimum_required(VERSION 3.8)
project(abs)

set(CMAKE_CXX_STANDARD 20)

add_executable(abs
        src/main.cc
        src/libFK.cc
        src/libFK.hh
        src/src.cc
        src/src.hh
)
