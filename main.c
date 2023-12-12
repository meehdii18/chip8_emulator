#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main() {

    RAM* chip8_ram = initializeRAM();

    /**********************************************************
     Testing write and read ram function
     ***********************************************************/
    uint16_t myadress = 0xFFF;
    uint8_t myvalue = 0xFA;
    writeRAM(chip8_ram,myadress,myvalue);
    uint8_t result = readRAM(chip8_ram,myadress);
    if( result == myvalue ){
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].",myvalue, myadress,result);
    }else{
        printf("Initial value to write : [%u] | Address in the ram : [%u] | Value at that address in the ram : [%u].\nERROR : Wrong value at the address.\n",myvalue, myadress,result);
    }

    /**********************************************************
     Testing ....
     ***********************************************************/

    freeRAM(chip8_ram);
    return 0;
}
