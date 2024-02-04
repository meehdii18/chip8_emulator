#include "cpu.h"

/**
 * \file machine.h
 * \brief Contains the CHIP8 virtual machine structure and all related functions declarations
 */


/**
 * \struct chip8
 * \brief Virtual machine representing the CHIP8
 */
typedef struct {
    Cpu *processor;

    Ram *memory;

    struct Display *display;

    struct Keyboard *keyboard;

    struct Speaker *speaker;

} Machine;

Machine *Machine_new(void);

/**
 * Initialize the CHIP8 emulator and all related components such as CPU, Display, Keyboard, Speaker and default sprites.
 */
void Machine_init(Machine *machine);

/**
 * Free the machine and all related components from the computer memory.
 */
void Machine_delete(Machine *machine);

/**
 * Destroy the CPU of the machine.
 */
void Machine_destroy(Machine *machine);

/**
 * Load a rom into the emulator memory
 * @param machine The emulator that will run the rom
 * @param rom_file Path to the rom file
 */
void Machine_load(Machine *machine, char *rom_file);

/**
 * Start the emulator
 * @param machine
 */
void Machine_run(Machine *machine);