cmake_minimum_required(VERSION 3.24)
project(list C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -pedantic -Wextra -std=c2x -m64 -Wno-unused-function)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -O0 -DASSERT_ENABLED")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Werror")

file(GLOB DOUBLY_LINKED_SOURCES "src/doubly-linked-list/*.c" "src/doubly-linked-list/include/*.h")
add_library(doubly_linked STATIC ${DOUBLY_LINKED_SOURCES})
target_include_directories(doubly_linked PRIVATE "src/doubly-linked-list/include" "include")

file(GLOB VEC_SOURCES "src/vec/*.c" "src/vec/include/*.h")
add_library(vec STATIC ${VEC_SOURCES})
target_include_directories(vec PRIVATE "src/vec/include" "include")

add_library(log STATIC "src/log.c" "include/log.h")
target_include_directories(log PRIVATE "include")

add_executable(listfun "src/main.c")
target_include_directories(listfun PRIVATE "include" "src/vec/include")
target_link_libraries(listfun vec doubly_linked log)