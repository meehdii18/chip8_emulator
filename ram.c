#include "ram.h"

RAM* newRAM(){
    RAM* ram = malloc(sizeof(RAM));
    if (ram == NULL){
        fprintf(stderr, "Error : RAM structure allocation failed.\n");
        return NULL;
    }

    ram->ram = malloc(sizeof(uint8_t) * 4096);
    if (ram->ram == NULL){
        fprintf(stderr, "Error: ram initialization failed.\n");
        free(ram);
        return NULL;
    }
    return ram;
}

int deleteRAM(RAM* ram){
    free(ram->ram);
    free(ram);
    return 0;
}

uint8_t readRAM(RAM* ram,uint16_t address){
    if (address >= 4096){
        fprintf(stderr, "Error : Address out of range.\n");
        exit(EXIT_FAILURE);
    }
    return ram->ram[address];
}

int writeRAM(RAM* ram, uint16_t address, uint8_t value){
    if (address >= 4096){
        fprintf(stderr,"Error : Address out of range.\n");
        return 1;
    }
    ram->ram[address] = value;
    return 0;
}