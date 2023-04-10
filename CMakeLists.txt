cmake_minimum_required(VERSION 3.24)
project(list CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES "src/*.cpp" "src/*.h")

add_executable(list ${SOURCES})
