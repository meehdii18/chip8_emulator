#include "cpu.h"

Processor* newProcessor(){
    Processor*cpu = calloc(1, sizeof(Processor)); // calloc : everything to 0
    if(cpu == NULL){
        fprintf(stderr,"Error : Processor allocation failed.\n");
        return NULL;
    }
    cpu->PC = 0x200; //0x200 : 0x000 to 0x1FF reserved for interpreter
    return cpu;
}

int deleteProcessor(Processor* cpu){
    if(cpu == NULL){
        fprintf(stderr,"Error : Cant free a NULL Processor.\n");
        return 1;
    }
    free(cpu);

    return 0;
}

void RET(Processor* cpu){
    assert(cpu);
     cpu->PC = cpu->stack[cpu->SP];
     cpu->SP--;

}

void JP_addr(Processor* cpu, uint16_t adr){
    assert(cpu);
     cpu->PC = adr;
}

void CALL_addr(Processor* cpu, uint16_t adr){
    assert(cpu);
    cpu->SP++;
    cpu->stack[cpu->SP] = cpu->PC;
    cpu->PC = adr;
}

void SE_Vx(Processor* cpu, uint8_t value,uint8_t x){
    assert(cpu);
    if(cpu->V[x] == value){
        cpu->PC += 2;
    }
}

void SNE_Vx(Processor* cpu, uint8_t value,uint8_t x){
    assert(cpu);
    if(cpu->V[x] != value){
        cpu->PC += 2;
    }
}

void SE_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    if(cpu->V[x] == cpu->V[y]){
        cpu->PC += 2;
    }
}

void LD_Vx(Processor* cpu, uint8_t x, uint8_t value){
    assert(cpu);
    cpu->V[x] = value;
}

void ADD_Vx(Processor* cpu, uint8_t x,uint8_t value){
    assert(cpu);
    cpu->V[x] += value;
}