#include "ram.h"

RAM* newRAM(){
    RAM* ram = malloc(sizeof(RAM));
    if (ram == NULL){
        fprintf(stderr, "Error : RAM structure allocation failed.\n");
        return NULL;
    }

    ram->cell = malloc(sizeof(uint8_t) * 4096);
    if (ram->cell == NULL){
        fprintf(stderr, "Error: RAM array allocation failed.\n");
        free(ram);
        return NULL;
    }
    return ram;
}

int deleteRAM(RAM* ram){
    free(ram->cell);
    free(ram);
    return 0;
}

uint8_t readRAM(RAM* ram,uint16_t adr){
    if(ram == NULL){
        fprintf(stderr,"Error : Can't read in a NULL ram.\n");
        exit(EXIT_FAILURE);
    }
    if (adr >= 4096){
        fprintf(stderr, "Error : Address out of range.\n");
        exit(EXIT_FAILURE);
    }
    return ram->cell[adr];
}

void writeRAM(RAM* ram, uint16_t adr, uint8_t value){
    if(ram == NULL){
        fprintf(stderr,"Error : Can't write to a NULL ram.\n");
        exit(EXIT_FAILURE);
    }
    if (adr >= 4096){
        fprintf(stderr,"Error : Address out of range.\n");
        exit(EXIT_FAILURE);
    }else{
        ram->cell[adr] = value;
    }
}