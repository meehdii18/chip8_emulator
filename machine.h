#ifndef CHIP8_EMULATOR_MACHINE_H
#define CHIP8_EMULATOR_MACHINE_H

#include "cpu.h"
#include "ram.h"
//#include "libprovided/lib/release/x64/libprovided.a"

/**
 * \file machine.h
 * \brief Contains the CHIP8 virtual machine structure and all related functions declarations
 */


/**
 * \struct chip8
 * \brief Virtual machine representing the CHIP8
 */
typedef struct Machine{
    struct Processor* cpu; /*!< Processor of the machine */
    struct RAM* ram;
    // struct Display display; /*!< Display of the machine */
    // struct Keyboard keyboard; /*!< Keyboard / Controller of the machine */
    // struct Speaker speaker; /*!< Speaker of the machine */
}Machine;

/**
 * Initialize the CHIP8 emulator
 * @return
 */
Machine Machine_init();

/**
 * Load a rom into the emulator
 * @param machine
 * @param rom
 */
void Machine_load(Machine machine,const char* rom);

/**
 * Loop that represent one cycle of the machine
 * @param machine
 */
void Machine_loop(Machine machine);

#endif //CHIP8_EMULATOR_MACHINE_H
