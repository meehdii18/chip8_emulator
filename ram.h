#ifndef CHIP8_RAM_H
#define CHIP8_RAM_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * \file ram.h
 * \brief Contains the ram memory data structure and all related functions declarations
 */

/**
 * \struct RAM
 * \brief Memory structure of the emulated CHIP 8
 */
typedef struct RAM {
    uint8_t* cell; /*!< Pointer to an array of 8 bits representing the memory cells */
} RAM;

/**
 * Initialize the ram memory structure
 * @return A pointer to the ram structure if success, NULL if it failed
 */
RAM* newRAM();

/**
 * Frees the memory allocated for the RAM structure.
 * @param ram A pointer to the ram structure to free
 * @return 0 if the ram was successfully freed
 */
int deleteRAM(RAM* ram);

/**
 * Function to read the value at a given address in a ram cell
 * @param a pointer to the RAM struct to read
 * @param adr The address in the RAM from where the value will be read
 * @return he value at the specified address in the RAM if the adr is valid, 1 if the address is out of range
 */
uint8_t readRAM(RAM* ram,uint16_t adr);

/**
 * Function to write to a given address in a cell
 * @param ram The ram to write in
 * @param adr The cell address to write in
 * @param value The value to store in the address
 * @return 0 if the value was successfully written into the cell, 1 if it is out of range
 */
void writeRAM(RAM* ram, uint16_t adr, uint8_t value);


#endif //CHIP8_RAM_H
