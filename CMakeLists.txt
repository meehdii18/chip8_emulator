cmake_minimum_required(VERSION 3.27)
project(chip8_emulator C)

set(CMAKE_C_STANDARD 11)

link_directories(/Library/Frameworks)

find_package(SDL2 REQUIRED COMPONENTS SDL2)


add_executable(chip8_emulator
        cpu.c
        cpu.h
        main.c
        ram.c
        ram.h
        chip8.h
        chip8.c)

target_link_libraries(chip8_emulator PRIVATE SDL2::SDL2)