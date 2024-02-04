cmake_minimum_required(VERSION 3.27)
project(Chip8_Emulator C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/release/x64)

add_executable(Chip8_Emulator main.c
        cpu.c
        ram.c
        machine.c
        machine.h)
target_link_libraries(Chip8_Emulator provided ${SDL2_LIBRARIES} -lm)
