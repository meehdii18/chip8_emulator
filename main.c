#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main() {

    RAM* chip8_ram = initializeRAM();

    /**********************************************************
     Testing write and read ram function
     ***********************************************************/
    uint16_t address = 0xFFF;
    uint8_t value = 0xFA;
    writeRAM(chip8_ram, address, value);
    uint8_t result = readRAM(chip8_ram, address);
    if(result == value ){
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].", value, address, result);
    }else{
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].\nERROR : Wrong value at the address.\n", value, address, result);
    }

    /**********************************************************
     Testing ....
     ***********************************************************/

    freeRAM(chip8_ram);
    return 0;
}
