cmake_minimum_required(VERSION 3.10)
project(graph_program C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(graph_program
    src/main.c
    src/input.c
    src/graph_operations.c
    src/bfs.c
    src/cycles.c
)

target_include_directories(graph_program PRIVATE include)

if (MSVC)
    target_compile_options(graph_program PRIVATE /W4)
else()
    target_compile_options(graph_program PRIVATE -Wall -Wextra)
endif()
