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

void RET(Processor* cpu){ // 00EE
    assert(cpu);
     cpu->PC = cpu->stack[cpu->SP];
     cpu->SP--;

}

void JP_addr(Processor* cpu, uint16_t adr){ // 1nnn
    assert(cpu);
     cpu->PC = adr;
}

void CALL_addr(Processor* cpu, uint16_t adr){ // 2nnn
    assert(cpu);
    cpu->SP++;
    cpu->stack[cpu->SP] = cpu->PC;
    cpu->PC = adr;
}

void SE_Vx(Processor* cpu, uint8_t value,uint8_t x){ // 3xkk
    assert(cpu);
    if(cpu->V[x] == value){
        cpu->PC += 2;
    }
}

void SNE_Vx(Processor* cpu, uint8_t value,uint8_t x){ // 4xkk
    assert(cpu);
    if(cpu->V[x] != value){
        cpu->PC += 2;
    }
}

void SE_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 5xy0
    assert(cpu);
    if(cpu->V[x] == cpu->V[y]){
        cpu->PC += 2;
    }
}

void LD_Vx_Byte(Processor* cpu, uint8_t x, uint8_t value){ // 6xkk
    assert(cpu);
    cpu->V[x] = value;
}

void ADD_Vx_Byte(Processor* cpu, uint8_t x,uint8_t value){ // 7xkk
    assert(cpu);
    cpu->V[x] += value;
}

void LD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy0
    assert(cpu);
    cpu->V[x] = cpu->V[y];
}

void OR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy1
    assert(cpu);
    cpu->V[x] = cpu->V[x] || cpu->V[y];
}

void AND_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy2
    assert(cpu);
    cpu->V[x] = cpu->V[x] && cpu->V[y];
}

void XOR_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy3
    assert(cpu);
    cpu->V[x] = cpu->V[x] ^ cpu->V[y];
}

void ADD_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy4
    uint8_t temp = cpu->V[x] + cpu->V[y];
    if(temp > 255){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] = temp & 0xFF; // binary mask
}

void SUB_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy5
    assert(cpu);
    if(cpu->V[x] > cpu->V[y]){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHR_Vx(Processor *cpu, uint8_t x){ // 8xy6
    assert(cpu);
    if (cpu->V[x] & 0x01){ // 0x01 = 00000001
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] = cpu->V[x] / 2;
}

void SUBN_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y){ // 8xy7
    assert(cpu);
    if(cpu->V[y] > cpu->V[x]){
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHL_Vx(Processor* cpu, uint8_t x){ // 8xyE
    assert(cpu);
    if(cpu->V[x] & 0x80){ // 0x80 = 10000000
        cpu->V[0xF] = 1;
    }else{
        cpu->V[0xF] = 0;
    }
}

void SNE_Vx_Vy(Processor* cpu, uint8_t x,uint8_t y){ // 9xy0
    assert(cpu);
    if(cpu->V[x] != cpu->V[y]){
        cpu->PC += 2;
    }
}

void LD_I(Processor* cpu, uint16_t value){ // Annn
    assert(cpu);
    cpu->I = value;
}

void JP_V0(Processor* cpu, uint16_t value){ // Bnnn
    assert(cpu);
    cpu->PC = cpu->V[0] + value;
}

void RND_Vx(Processor* cpu, uint8_t x, uint8_t kkk){ // Cxkk
    assert(cpu);
    uint8_t randInt = rand() % 256;
    cpu->V[x] = randInt & kkk;
}

void DRW_Vx_Vy(Processor* cpu, uint8_t x, uint8_t y, uint8_t n){ // Dxyn
    assert(cpu);
    // pas possible pour l'instant
}

void SKP_Vx(Processor* cpu,uint8_t x){ // Ex9E
    assert(cpu);
    // pas possible pour l'instant
}

void SNKP_Vx(Processor* cpu,uint8_t x){ // ExA1
    assert(cpu);
    // pas possible pour l'instant
}

void LD_Vx_DT(Processor* cpu,uint8_t x){ // Fx07
    assert(cpu);
    cpu->V[x] = cpu->DT;
}

void LD_DT_K(Processor* cpu, uint8_t x){ // Fx0A
    assert(cpu);
    // pas possible pour l'instant
}

void LD_DT_Vx(Processor* cpu, uint8_t x){ // Fx15
    assert(cpu);
    cpu->DT = cpu->V[x];
}

void LD_ST_Vx(Processor* cpu, uint8_t x){ // Fx18
    assert(cpu);
    cpu->ST = cpu->V[x];
}

void ADD_I_Vx(Processor* cpu, uint8_t x){ // Fx1E
    assert(cpu);
    cpu->I += cpu->V[x];
}

void LD_F_Vx(Processor* cpu, uint8_t x){ // Fx29
    assert(cpu);
    // pas possible pour l'instant
}

void LD_B_Vx(Processor* cpu, uint8_t x,RAM* ram){ // Fx33
    assert(cpu);
    assert(ram);
    uint8_t value = cpu->V[x];

    uint8_t hundreds = value / 100;
    uint8_t tens = (value%100) /10;
    uint8_t ones = value % 10;

    writeRAM(ram,cpu->I,hundreds);
    writeRAM(ram,cpu->I + 1, tens);
    writeRAM(ram,cpu->I+2, ones);
}

void LD_I_Vx(Processor* cpu,uint8_t x,RAM* ram){ // Fx55
    assert(cpu);
    assert(ram);

    for (uint16_t i = 0; i <= x; i++){
        writeRAM(ram,cpu->I+i,cpu->V[i]);
    }
}

void LD_Vx_I(Processor* cpu, uint8_t x, RAM* ram){ // Fx65
    assert(cpu);
    assert(ram);

    for (uint16_t i = 0; i <= x; i++){
        cpu->V[i] = readRAM(ram, cpu->I+i);
    }
}