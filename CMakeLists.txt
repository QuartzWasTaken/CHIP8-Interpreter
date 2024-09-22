cmake_minimum_required(VERSION 3.10)
project(CHIP8)
add_executable(oCHIP CHIP8.cpp opcodes.cpp)
include_directories(CHIP8 PUBLIC "/home/gab/projects/CHIP8/include")
