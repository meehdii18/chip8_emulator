#ifndef CHIP8_EMULATOR_MACHINE_H
#define CHIP8_EMULATOR_MACHINE_H

#include "cpu.h"
#include "ram.h"


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
    struct Display *display; /*!< Display of the machine */
    struct Keyboard *keyboard; /*!< Keyboard / Controller of the machine */
    struct Speaker *speaker; /*!< Speaker of the machine */
}Machine;

/**
 *
 * @param cpu
 */
void Load_sprite(Processor *cpu);

/**
 * Initialize the CHIP8 emulator
 * @return
 */
Machine* Machine_init();

/**
 * Destroy the CHIP8 emulator
 */
void Machine_destroy(Machine* machine);

/**
 * Load a rom into the emulator
 * @param machine
 * @param rom
 * @return 1 if success, 0 if not
 */
int Machine_load(Machine* machine,const char* rompath);

/**
 * Loop that represent one cycle of the machine cpu
 * @param machine
 */
void Machine_loop(Machine* machine);




#endif //CHIP8_EMULATOR_MACHINE_H
