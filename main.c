#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "cpu.h"

int main() {

    RAM* chip8_ram = newRAM();
    Processor* chip8_cpu = newProcessor(chip8_ram);

    /*
     Testing write and read cell function
    */

    // NORMAL CASE
    uint16_t address = 0xFFF;
    uint8_t value = 0xFA;
    writeRAM(chip8_ram, address,value);
    uint8_t result = readRAM(chip8_ram, address);
    if(result == value ){
        printf("Initial value to write : [%u]\nAddress in the cell : [%u]\nValue at that address in the cell : [%u]\n\n", value, address, result);
    }else{
        printf("Initial value to write : [%u]\nAddress in the cell : [%u]\nValue at that address in the cell : [%u].\nERROR : Wrong value at the address\n\n", value, address, result);
    }


    // ERROR CASE
    //uint8_t test = readRAM(chip8_ram, 9000);

    /*
     Testing some processor function
    */

    JP_addr(chip8_cpu,0x82);
    printf("JP_Addr to 0x82 (130)...\nPC : %hu\n\n",chip8_cpu->PC);

    printf("SP : %hu | PC : %hu\n",chip8_cpu->SP,chip8_cpu->PC);
    CALL_addr(chip8_cpu,0x90);
    printf("CALL_addr to 0x90 (144)...\nSP : %hu | PC : %hu\n\n",chip8_cpu->SP,chip8_cpu->PC);

    printf("V[A] : %hu\n",chip8_cpu->V[0xA]);
    LD_Vx_Byte(chip8_cpu,0xA,15);
    printf("LD_Vx_Byte : 15 in V[A] ...\nV[A] : %hu\n\n",chip8_cpu->V[0xA]);


    deleteRAM(chip8_ram);
    deleteProcessor(chip8_cpu);

    return 0;
}