cmake_minimum_required(VERSION 3.8)
project(abs)

set(CMAKE_CXX_STANDARD 20)

add_executable(abs
        main.cc
        libFK.cc
        libFK.hh
        src.cc
        src.hh
        progressBar.cc
        progressBar.hh
)

set(RESOURCES_DIR "${CMAKE_INSTALL_PREFIX}/share/abs/res")

install(TARGETS abs DESTINATION /usr/local/bin)

install(DIRECTORY res/ DESTINATION ${RESOURCES_DIR})