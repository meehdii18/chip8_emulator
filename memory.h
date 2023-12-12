#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Memory structure of the ram
 */
typedef struct RAM {
    uint8_t* ram;
} RAM;

/**
 * Function to initialize the ram memory
 * @return ram structure
 */
RAM* initializeRAM();

/**
 * Function to free the ram memory
 * @return 0 if success
 */
int freeRAM(RAM* ram);

/**
 * Function to read the value at a given address in a ram
 * @param ram The ram to write in
 * @param address The address to read from
 * @return the value at the adress, 1 if error
 */
uint8_t readRAM(RAM* ram,uint16_t address);

/**
 * Function to write to a given address in a ram
 * @param ram The ram to write in
 * @param address The address to write in the ram
 * @param value The value to store in the address
 * @return 0 if success, 1 if error
 */
int writeRAM(RAM* ram, uint16_t address, uint8_t value);


#endif //CHIP8_MEMORY_H
