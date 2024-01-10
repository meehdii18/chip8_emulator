#ifndef CHIP8_EMULATOR_CHIP8_H
#define CHIP8_EMULATOR_CHIP8_H

#include "cpu.h"
#include "ram.h"

/**
 * \file chip8.h
 * \brief Contains the CHIP8 virtual machine structure and all related functions declarations
 */


/**
 * \struct chip8
 * \brief Virtual machine representing the CHIP8
 */
typedef struct chip8{
    struct Processor* cpu; /*!< Processor of the machine */
    //display /*!< Display of the machine */
    //keyboard or controller /*!< Keyboard / Controller of the machine */
    //speaker /*!< Speaker of the machine */
}chip8;

#endif //CHIP8_EMULATOR_CHIP8_H
