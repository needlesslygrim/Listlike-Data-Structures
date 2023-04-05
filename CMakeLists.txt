cmake_minimum_required(VERSION 3.24)
project(List C)

set(CMAKE_C_STANDARD 17)

file(GLOB SOURCES "src/*.c" "src/*.h")

add_executable(List ${SOURCES})
