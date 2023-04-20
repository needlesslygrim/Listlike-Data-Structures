cmake_minimum_required(VERSION 3.24)
project(list CXX)
set(CMAKE_CXX_STANDARD 23)


add_compile_options(-Wall -pedantic -Wextra)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror")


file(GLOB SOURCES "src/*.cpp" "src/*.h")

add_executable(list ${SOURCES})
