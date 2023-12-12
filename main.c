#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main() {

    RAM* chip8_ram = initializeRAM();

    /**********************************************************
     Testing write and read ram function
     ***********************************************************/

    // NORMAL CASE
    uint16_t address = 0xFFF;
    uint8_t value = 0xFA;
    writeRAM(chip8_ram, address, value);
    uint8_t result = readRAM(chip8_ram, address);
    if(result == value ){
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].\n", value, address, result);
    }else{
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].\nERROR : Wrong value at the address.\n", value, address, result);
    }

    // ERROR CASE
    uint8_t test = readRAM(chip8_ram, 9000);

    /**********************************************************
     Testing processor base function
     ***********************************************************/

    freeRAM(chip8_ram);
    return 0;
}
