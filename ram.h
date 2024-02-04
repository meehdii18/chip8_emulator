#ifndef RAM_HEADER_GUARD
#define RAM_HEADER_GUARD

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \file ram.h
 * \brief Contains the ram memory data structure and all related functions declarations
 */

/**
 * \struct RAM
 * \brief Memory structure of the emulated CHIP 8
 */
typedef struct {
    uint8_t *tab;/*!< Pointer to an array of 8 bits representing the memory cells */
} Ram;

/**
 * Initialize the ram memory structure
 * @return A pointer to the ram structure if success, NULL if it failed
 */
Ram *Ram_new(void);

/**
 * Allocate the memory for the RAM Cells.
 */
void Ram_init(Ram *memory);

/**
 * Frees the memory allocated for the RAM structure.
 * @param memory A pointer to the ram structure to free
 */
void Ram_delete(Ram *memory);

/**
 * Frees the memory allocated for the RAM Cells.
 * @param memory A pointer to the ram structure to destroy
 */
void Ram_destroy(Ram *memory);

/**
 * Function to write to a given address in a cell
 * @param memory The ram to write in
 * @param address The cell address to write in
 * @param value The value to store in the address
 */
void Ram_write(Ram *memory, uint16_t address, uint8_t value);

/**
 * Function to read the value at a given address in a ram cell
 * @param memory A pointer to the RAM struct to read in
 * @param address The address in the RAM from where the value will be read
 * @return The value at the specified address in the RAM if the adr is valid, 1 if the address is out of range
 */
uint8_t Ram_read(Ram *memory, uint16_t address);

#endif