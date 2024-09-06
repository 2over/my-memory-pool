cmake_minimum_required(VERSION 3.14)
project(my_memory_pool)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_memory_pool main.cpp
        include/memory/memory_cell.h
        include/memory/memory_chunk.h
        src/memory/memory_cell.cpp
        src/memory/memory_chunk.cpp
        include/gc/gc_factory.h
        include/memory/memory_pool.h
        src/memory/memory_pool.cpp
)
