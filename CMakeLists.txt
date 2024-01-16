cmake_minimum_required(VERSION 3.27)
project(chip8_emulator C)

set(CMAKE_C_STANDARD 17)

link_directories(libprovided/lib/release/x64)
include_directories(libprovided/include)

set(SDL2_PATH "/usr/include/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(chip8_emulator
        cpu.c
        cpu.h
        main.c
        ram.c
        ram.h
        machine.h
        machine.c)

target_link_libraries(chip8_emulator PRIVATE -lm ${CMAKE_SOURCE_DIR}/libprovided/lib/release/x64/libprovided.a)
target_link_libraries(chip8_emulator PRIVATE -lm SDL2)