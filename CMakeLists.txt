cmake_minimum_required(VERSION 3.24)
project(list C)
set(CMAKE_C_STANDARD 23)


add_compile_options(-Wall -pedantic -Wextra)
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Werror")


file(GLOB SOURCES "src/*.c" "src/*.h")
list(REMOVE_ITEM SOURCES "src/main.c")

add_library(list STATIC ${SOURCES})

add_executable(listfun "src/main.c")

target_link_libraries(listfun list)