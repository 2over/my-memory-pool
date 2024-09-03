cmake_minimum_required(VERSION 3.28)
project(my_memory_pool)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_memory_pool main.cpp
        include/memory/memory_cell.h
        include/memory/memory_chunk.h)
