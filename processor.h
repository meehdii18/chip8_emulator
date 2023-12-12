#ifndef CHIP8_PROCESSOR_H
#define CHIP8_PROCESSOR_H

#include "memory.h"

typedef struct Processor{
    uint8_t V[16]; // 16 general purpose 8-bit registers, referred to as V0, V1, ..., VF
    uint16_t I; // a 16-bit register called I, generally used to store memory addresses
    uint8_t ST; // Sound timer register
    uint8_t DT; // Delay timer register
    uint16_t PC; // a 16-bit register, called program counter or PC, used to store the address of the instruction currently being executed
    uint8_t SP; // Pointer to the topmost level of the stack
    uint16_t stack[16]; // a 16 16-bit values array to store the addresses that the interpreter should return to when a subroutine terminates.
} Processor;

#endif //CHIP8_PROCESSOR_H
