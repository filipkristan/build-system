cmake_minimum_required(VERSION 3.8)
project(abs)

set(CMAKE_CXX_STANDARD 20)

add_executable(abs
        main.cc
        libFK.cc
        libFK.hh
        src.cc
        src.hh
)
