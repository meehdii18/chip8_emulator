#ifndef CHIP8_EMULATOR_CHIP8_H
#define CHIP8_EMULATOR_CHIP8_H

#include "cpu.h"
#include "ram.h"
// #include "libprovided/lib/release/x64/libprovided.a"

/**
 * \file chip8.h
 * \brief Contains the CHIP8 virtual machine structure and all related functions declarations
 */


/**
 * \struct chip8
 * \brief Virtual machine representing the CHIP8
 */
typedef struct emulator{
    struct Processor* cpu; /*!< Processor of the machine */
    struct RAM* ram;
    // struct Display display; /*!< Display of the machine */
    // struct Keyboard keyboard; /*!< Keyboard / Controller of the machine */
    // struct Speaker speaker; /*!< Speaker of the machine */
}chip8;

#endif //CHIP8_EMULATOR_CHIP8_H
