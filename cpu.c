#include "cpu.h"

Processor* newProcessor(){
    Processor*cpu = calloc(1, sizeof(Processor)); // calloc : everything to 0
    if(cpu == NULL){
        fprintf(stderr,"Error : CPU allocation failed.\n");
        return NULL;
    }
    cpu->PC = 0x200; //0x200 : 0x000 to 0x1FF reserved for interpreter
    return cpu;
}

int deleteProcessor(Processor* cpu){
    if(cpu == NULL){
        fprintf(stderr,"Error : Cannot free a NULL Processor\n");
        return 1;
    }
    free(cpu);

    return 0;
}