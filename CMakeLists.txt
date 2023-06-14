cmake_minimum_required(VERSION 3.24)
project(list C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -pedantic -Wextra -std=c2x -m64)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Werror")

file(GLOB DOUBLY_LINKED_SOURCES "src/doubly-linked-list/*.c" "src/doubly-linked-list/*.h")
add_library(doubly_linked STATIC ${DOUBLY_LINKED_SOURCES})

file(GLOB VEC_SOURCES "src/vec/*.c" "src/vec/*.h")
add_library(vec STATIC ${VEC_SOURCES})

add_library(log STATIC "src/log.h" "src/log.c")

add_executable(listfun "src/main.c")

target_link_libraries(listfun vec doubly_linked log)