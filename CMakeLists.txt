cmake_minimum_required(VERSION 3.24)
project(list C)

set(CMAKE_C_STANDARD 17 )

file(GLOB SOURCES "src/*.c" "src/*.h")

add_executable(list ${SOURCES})
