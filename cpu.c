#include "cpu.h"

Processor *newProcessor(RAM *ram) {
    Processor *cpu = calloc(1, sizeof(Processor)); // calloc : everything to 0
    if (cpu == NULL) {
        fprintf(stderr, "Error : Processor allocation failed.\n");
        return NULL;
    }
    cpu->PC = 0x200; //0x200 : 0x000 to 0x1FF reserved for interpreter
    cpu->ram = ram;
    return cpu;
}

void deleteProcessor(Processor *cpu) {
    if (cpu == NULL) {
        fprintf(stderr, "Error : Cant free a NULL Processor.\n");
        return;
    }
    free(cpu);
}

void CLS(struct Display *display) { // 00E0
    assert(display);
    Display_CLS(display);
}

void RET(Processor *cpu) { // 00EE
    assert(cpu);
    cpu->PC = cpu->stack[cpu->SP];
    cpu->SP--;

}

void JP_addr(Processor *cpu, uint16_t adr) { // 1nnn
    assert(cpu);
    cpu->PC = adr;
}

void CALL_addr(Processor *cpu, uint16_t adr) { // 2nnn
    assert(cpu);
    cpu->SP++;
    cpu->stack[cpu->SP] = cpu->PC;
    cpu->PC = adr;
}

void SE_Vx(Processor *cpu, uint8_t value, uint8_t x) { // 3xkk
    assert(cpu);
    if (cpu->V[x] == value) {
        cpu->PC += 2;
    }
}

void SNE_Vx(Processor *cpu, uint8_t value, uint8_t x) { // 4xkk
    assert(cpu);
    if (cpu->V[x] != value) {
        cpu->PC += 2;
    }
}

void SE_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 5xy0
    assert(cpu);
    if (cpu->V[x] == cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_Vx_Byte(Processor *cpu, uint8_t x, uint8_t value) { // 6xkk
    assert(cpu);
    cpu->V[x] = value;
}

void ADD_Vx_Byte(Processor *cpu, uint8_t x, uint8_t value) { // 7xkk
    assert(cpu);
    cpu->V[x] += value;
}

void LD_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy0
    assert(cpu);
    cpu->V[x] = cpu->V[y];
}

void OR_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy1
    assert(cpu);
    cpu->V[x] = cpu->V[x] | cpu->V[y];
}

void AND_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy2
    assert(cpu);
    cpu->V[x] = cpu->V[x] & cpu->V[y];
}

void XOR_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy3
    assert(cpu);
    cpu->V[x] = cpu->V[x] ^ cpu->V[y];
}

void ADD_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy4
    uint16_t temp = cpu->V[x] + cpu->V[y];
    if (temp > 255) {
        cpu->V[0xF] = 1;
    } else {
        cpu->V[0xF] = 0;
    }
    cpu->V[x] = temp & 0xFF; // binary mask
}

void SUB_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy5
    assert(cpu);
    if (cpu->V[x] > cpu->V[y]) {
        cpu->V[0xF] = 1;
    } else {
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHR_Vx(Processor *cpu, uint8_t x) { // 8xy6
    assert(cpu);
    cpu->V[0xF] = cpu->V[x] & 0x01; // 0x01 = 00000001
    cpu->V[x] = cpu->V[x] >> 1;
}

void SUBN_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 8xy7
    assert(cpu);
    if (cpu->V[y] > cpu->V[x]) {
        cpu->V[0xF] = 1;
    } else {
        cpu->V[0xF] = 0;
    }
    cpu->V[x] -= cpu->V[y];
}

void SHL_Vx(Processor *cpu, uint8_t x) { // 8xyE
    assert(cpu);
    cpu->V[0xF] = cpu->V[x] & 0x80; // 0x80 = 10000000
    cpu->V[x] = cpu->V[x] >> 1;
}

void SNE_Vx_Vy(Processor *cpu, uint8_t x, uint8_t y) { // 9xy0
    assert(cpu);
    if (cpu->V[x] != cpu->V[y]) {
        cpu->PC += 2;
    }
}

void LD_I(Processor *cpu, uint16_t value) { // Annn
    assert(cpu);
    cpu->I = value;
}

void JP_V0(Processor *cpu, uint16_t value) { // Bnnn
    assert(cpu);
    cpu->PC = cpu->V[0] + value;
}

void RND_Vx(Processor *cpu, uint8_t x, uint8_t kkk) { // Cxkk
    assert(cpu);
    cpu->V[x] = (rand() % 256) & kkk;
}

void DRW_Vx_Vy(Processor *cpu, struct Display *display, uint8_t x, uint8_t y, uint8_t n) { // Dxyn
    struct Sprite sprite;
    Sprite_init(&sprite,n);
    for(int i=0;i<n;i++){
        Sprite_add(&sprite,readRAM(cpu->ram, cpu->I+i));
    }
    Display_DRW(display,&sprite,cpu->V[x],cpu->V[y],&cpu->V[0xF]);
    Sprite_destroy(&sprite);
}

void SKP_Vx(Processor *cpu, struct Keyboard *keyboard, uint8_t x) { // Ex9E
    assert(cpu);
    assert(keyboard);
    if (Keyboard_get(keyboard,x) == 1) {
        cpu->PC += 2;
    }
}

void SNKP_Vx(Processor *cpu, struct Keyboard *keyboard, uint8_t x) { // ExA1
    assert(cpu);
    assert(keyboard);
    if (Keyboard_get(keyboard, x) == 0) {
        cpu->PC += 2;
    }
}

void LD_Vx_DT(Processor *cpu, uint8_t x) { // Fx07
    assert(cpu);
    cpu->V[x] = cpu->DT;
}

void LD_Vx_K(Processor *cpu, struct Keyboard *keyboard, uint8_t x) { // Fx0A
    assert(cpu);
    assert(keyboard);
    Keyboard_wait(keyboard, &cpu->V[x]);
}

void LD_DT_Vx(Processor *cpu, uint8_t x) { // Fx15
    assert(cpu);
    cpu->DT = cpu->V[x];
}

void LD_ST_Vx(Processor *cpu, uint8_t x) { // Fx18
    assert(cpu);
    cpu->ST = cpu->V[x];
}

void ADD_I_Vx(Processor *cpu, uint8_t x) { // Fx1E
    assert(cpu);
    cpu->I += cpu->V[x];
}

void LD_F_Vx(Processor *cpu, uint8_t x) { // Fx29
    assert(cpu);
    //on doit coder en mémoire les sprites des nombres hexadécimaux et mettre I à l'adresse du sprite de la valeur de x
}

void LD_B_Vx(Processor *cpu, uint8_t x) { // Fx33
    assert(cpu);
    uint8_t value = cpu->V[x];

    uint8_t hundreds = value / 100;
    uint8_t tens = (value % 100) / 10;
    uint8_t ones = value % 10;

    writeRAM(cpu->ram, cpu->I, hundreds);
    writeRAM(cpu->ram, cpu->I + 1, tens);
    writeRAM(cpu->ram, cpu->I + 2, ones);
}

void LD_I_Vx(Processor *cpu, uint8_t x) { // Fx55
    assert(cpu);

    for (uint16_t i = 0; i <= x; i++) {
        writeRAM(cpu->ram, cpu->I + i, cpu->V[i]);
    }
}

void LD_Vx_I(Processor *cpu, uint8_t x) { // Fx65
    assert(cpu);

    for (uint16_t i = 0; i <= x; i++) {
        cpu->V[i] = readRAM(cpu->ram, cpu->I + i);
    }
}

void fetch_decode_execute(Processor *cpu, struct Display *display, struct Keyboard *keyboard) {
    assert(cpu);
    assert(display);
    assert(keyboard);

    //fetch
    uint8_t part1 = readRAM(cpu->ram, cpu->PC);
    uint8_t part2 = readRAM(cpu->ram, cpu->PC + 1);
    uint16_t instruction = part1 << 8; // 8 bits left mask
    instruction += part2; // add part 2
    cpu->PC += 2;

    //decode and execute
    if (instruction == 0x0000) {
        if ((instruction & 0x000F) == 0x0000) { // 00E0
            CLS(display);
        } else if ((instruction & 0x000F) == 0x000E) { // 00EE
            RET(cpu);
        }


    } else if ((instruction & 0xF000) == 0x1000)  // 1nnn
        JP_addr(cpu, ((part1 & 0x0F)<<8) + part2);
    else if ((instruction & 0xF000) == 0x2000)  // 2nnn
        CALL_addr(cpu, ((part1 & 0x0F)<<8) + part2);
    else if ((instruction & 0xF000) == 0x3000)  // 3xkk
        SE_Vx(cpu, (part1 & 0x0F) >> 4, part2);
    else if ((instruction & 0xF000) == 0x4000)  // 4xkk
        SNE_Vx(cpu, (part1 & 0x0F) >> 4, part2);
    else if ((instruction & 0xF000) == 0x5000)  // 5xy0
        SE_Vx_Vy(cpu, (part1&0x0F), (part2>>4));
    else if ((instruction & 0xF000) == 0x6000) // 6xkk
        LD_Vx_Byte(cpu, (part1&0x0F), (part2));
    else if ((instruction & 0xF000) == 0x7000) // 7xkk
        ADD_Vx_Byte(cpu, part1&0x0F, part2);
    else if ((instruction & 0xF000) == 0x8000) // 8xy0
        LD_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8001) // 8xy1
        OR_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8002) // 8xy2
        AND_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8003) // 8xy3
        XOR_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8004) // 8xy4
        ADD_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8005) // 8xy5
        SUB_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x8006) // 8xy6
        SHR_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF00F) == 0x8007) // 8xy7
        SUBN_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF00F) == 0x800E) // 8xyE
        SHL_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF000) == 0x9000) // 9xy0
        SNE_Vx_Vy(cpu, part1&0x0F, part2>>4);
    else if ((instruction & 0xF000) == 0xA000) // Annn
        LD_I(cpu, ((part1 & 0x0F)<<8) + part2);
    else if ((instruction & 0xF000) == 0xB000) // Bnnn
        JP_V0(cpu, (instruction & 0x0FFF));
    else if ((instruction & 0xF000) == 0xC000) // Cxkk
        RND_Vx(cpu, part1&0x0F, part2);
    else if ((instruction & 0xF000) == 0xD000) // Dxyn
        DRW_Vx_Vy(cpu, display, (part1&0x0F) , (part2)>>4, (part2&0x0F));
    else if ((instruction & 0xF0FF) == 0xE09E) // Ex9E
        SKP_Vx(cpu, keyboard, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xE0A1) // ExA1
        SNKP_Vx(cpu, keyboard, part1&0x0F);
    else if ((instruction & 0xF00F) == 0xF007) // Fx07
        LD_Vx_DT(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF00A) // Fx0A
        LD_Vx_K(cpu, keyboard, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF015) // Fx15
        LD_DT_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF018) // Fx18
        LD_ST_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF01E) // Fx1E
        ADD_I_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF029) // Fx29
        LD_F_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF033) // Fx33
        LD_B_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF055) // Fx55
        LD_I_Vx(cpu, part1&0x0F);
    else if ((instruction & 0xF0FF) == 0xF065) // Fx65
        LD_Vx_I(cpu, part1&0x0F);
}



void decrement_timers(Processor* cpu){
    cpu->ST -= 1;
    cpu->DT -= 1;
}