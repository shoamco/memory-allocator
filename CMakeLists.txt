cmake_minimum_required(VERSION 3.14)
project(memory_memory_allocator_shoamco C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(memory_memory_allocator_shoamco
        MemoryAllocator.c)
