cmake_minimum_required(VERSION 3.10)
project(CHIP8)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} CHIP8.cpp opcodes.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "/home/gab/projects/CHIP8/include" "/usr/include/SDL2" "/usr/include/imgui")
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})