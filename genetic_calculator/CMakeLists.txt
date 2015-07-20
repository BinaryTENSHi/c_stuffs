cmake_minimum_required(VERSION 3.0)
project(genetic_calculator)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra")

set(SOURCE_FILES main.c)
add_executable(genetic_calculator ${SOURCE_FILES})
