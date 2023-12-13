#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include "ram.h"

/**
 * \file cpu.h
 * \brief Contains the processor data structure and all related functions declarations
 */

/**
 * \struct Processor
 * \brief CHIP 8 emulated processor and registre
 */
typedef struct Processor{
    uint8_t V[16]; /*!< 16 general purpose 8-bit registers, referred to as V0, V1, ..., VF */
    uint8_t ST; /*!< Sound timer register */
    uint8_t DT; /*!< Delay timer register */
    uint16_t PC; /*!< a 16-bit register, called program counter or PC, used to store the address of the instruction currently being executed */
    uint8_t SP; /*!< Pointer to the topmost level of the stack */
    uint16_t stack[16]; /*!< a 16 16-bit values array to store the addresses that the interpreter should return to when a subroutine terminates */
} Processor;


/**
 * Initializes the processor structure
 * @return A pointer to the initialized Processor structure, NULL if failed
 */
Processor* newProcessor();

/**
 *
 * @param cpu A pointer to the processor to free
 * @return 0 if success and 1 if failure
 */
int deleteProcessor(Processor* cpu);

#endif //CHIP8_CPU_H
