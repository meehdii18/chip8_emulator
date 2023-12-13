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

void LD_Vx_Byte(Processor* cpu, uint8_t x, uint8_t value){
    assert(cpu);
    cpu->V[x] = value;
}

void ADD_Vx_Byte(Processor* cpu, uint8_t x,uint8_t value){
    assert(cpu);
    cpu->V[x] += value;
}

void LD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    cpu->V[x] = cpu->V[y];
}

void OR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    cpu->V[x] = cpu->V[x] || cpu->V[y];
}

void AND_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    cpu->V[x] = cpu->V[x] && cpu->V[y];
}

void XOR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    cpu->V[x] = cpu->V[x] ^ cpu->V[y];
}

void ADD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    uint8_t temp = cpu->V[x] + cpu->V[y];
    if(temp > 255){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] = temp & 0xFF; // binary mask
}

void SUB_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    if(cpu->V[x] > cpu->V[y]){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHR_Vx(Processor *cpu, uint8_t x){
    assert(cpu);
    if (cpu->V[x] & 0x01){ // 0x01 = 00000001
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] = cpu->V[x] / 2;
}

void SUBN_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){
    assert(cpu);
    if(cpu->V[y] > cpu->V[x]){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHL_Vx(Processor* cpu, uint8_t x){
    assert(cpu);
    if(cpu->V[x] & 0x80){ // 0x80 = 10000000
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
}

void SNE_Vx_Vy(Processor* cpu, uint8_t x,uint8_t y){
    assert(cpu);
    if(cpu->V[x] != cpu->V[y]){
        cpu->PC += 2;
    }
}

void LD_I(Processor* cpu, uint16_t value){
    assert(cpu);
    cpu->I = value;
}

void JP_V0(Processor* cpu, uint16_t value){
    assert(cpu);
    cpu->PC = cpu->V[0] + value;
}

void RND_Vx(Processor* cpu, uint8_t x, uint8_t kkk){
    assert(cpu);
    uint8_t randInt = rand() % 256;
    cpu->V[x] = randInt & kkk;
}