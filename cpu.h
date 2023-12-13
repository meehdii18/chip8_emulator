#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include "ram.h"
#include <assert.h>

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
    uint16_t I; /*!< used to store memory addresses */
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

/**
 * Sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
 * @param cpu The processor that will execute the instruction
 */
void RET(Processor* cpu);

/**
 * Sets the program counter to adr.
 * @param cpu The processor that will execute the instruction
 * @param adr The address to use
 */
void JP_addr(Processor* cpu,u_int16_t adr);

/**
 * Increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to adr.
 * @param cpu The processor that will execute the instruction
 * @param adr The address that to
 */
void CALL_addr(Processor* cpu, uint16_t adr);

/**
 * Compares register Vx to kk, and if they are equal, increments the program counter by 2.
 * @param cpu
 * @param value
 * @param x
 */
void SE_Vx(Processor* cpu, uint8_t value,uint8_t x);

/**
 * Compares register Vx to kk, and if they are not equal, increments the program counter by 2.
 * @param cpu
 * @param value
 * @param x
 */
void SNE_Vx(Processor* cpu, uint8_t value,uint8_t x);

/**
 * Compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
 * @param cpu
 * @param x
 * @param y
 */
void SE_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y);

/**
 * Puts the value kk into register Vx.
 * @param cpu
 * @param x
 * @param value
 */
void LD_Vx(Processor* cpu, uint8_t x, uint8_t value);

/**
 * Adds the value kk to the value of register Vx, then stores the result in Vx.
 * @param cpu
 * @param x
 * @param value
 */
void ADD_Vx(Processor* cpu, uint8_t x, uint8_t value);

#endif //CHIP8_CPU_H
