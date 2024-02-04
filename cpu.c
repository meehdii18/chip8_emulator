#include <unistd.h>
#include "cpu.h"

//------------------------------------------------------
//-------------------Gestion structure------------------
//------------------------------------------------------

Cpu *Cpu_new(void) {
    Cpu *newCpu = calloc(1, sizeof(Cpu));
    Cpu_init(newCpu);

    return newCpu;
}

void Cpu_init(Cpu *processor) {
    assert(processor);
    processor->PC = 0x200;
}

void Cpu_delete(Cpu *processor) {
    assert(processor);
    Cpu_destroy(processor);
    free(processor);
}

void Cpu_destroy(Cpu *processor) {
    assert(processor);
}

void fetch_decode_execute(Cpu *processor) {

    uint16_t instruction;

    // FETCH
    instruction = Ram_read(processor->memory, processor->PC);
    instruction = instruction << 8;
    instruction |= Ram_read(processor->memory, processor->PC + 1);

    if (processor->PC < 0x0FFF) {
        processor->PC += 2;
    } else {
        sleep(1000);
    }

    // DECODE & EXECUTE
    switch (instruction & 0xF000) {
        case 0x0000 :
            if (instruction == 0x00E0) { //00E0
                CLS(processor);
            } else if (instruction == 0x00EE) { //00EE
                RET(processor);
            }
            break;
        case 0x1000 :
            JP_addr(processor, instruction & 0x0FFF); //1nnn
            break;
        case 0x2000 :
            CALL_addr(processor, instruction & 0x0FFF); //2nnn
            break;
        case 0x3000 :
            SE_Vx_byte(processor, (instruction & 0x0F00)>>8, instruction & 0x00FF); //3xkk
            break;
        case 0x4000 :
            SNE_Vx_byte(processor, (instruction & 0x0F00)>>8, instruction & 0x00FF); //4xkk
            break;
        case 0x5000 :
            SE_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //5xy0
            break;
        case 0x6000 :
            LD_Vx_byte(processor, (instruction & 0x0F00)>>8, instruction & 0x00FF); //6xkk
            break;
        case 0x7000 :
            ADD_Vx_byte(processor, (instruction & 0x0F00)>>8, instruction & 0x00FF); //7xkk
            break;
        case 0x8000 :
            switch (instruction & 0x000F) {
                case 0x000 :
                    LD_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy0
                    break;
                case 0x0001 :
                    OR_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy1
                    break;
                case 0x0002 :
                    AND_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy2
                    break;
                case 0x0003 :
                    XOR_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy3
                    break;
                case 0x0004 :
                    ADD_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy4
                    break;
                case 0x0005 :
                    SUB_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy5
                    break;
                case 0x0006 :
                    SHR_Vx(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy6
                    break;
                case 0x0007 :
                    SUBN_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xy7
                    break;
                case 0x000E :
                    SHL_Vx(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //8xyE
                    break;
            }
            break;
        case 0x9000 :
            SNE_Vx_Vy(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4); //9xy0
            break;
        case 0xA000 :
            LD_I_addr(processor, instruction & 0x0FFF); //Annn
            break;
        case 0xB000 :
            JP_V0_addr(processor, instruction & 0x0FFF); //Bnnn
            break;
        case 0xC000 :
            RND_Vx_byte(processor, (instruction & 0x0F00)>>8, instruction & 0x00FF); //Cxkk
            break;
        case 0xD000 :
            DRW_Vx_Vy_nibble(processor, (instruction & 0x0F00)>>8, (instruction & 0x00F0)>>4, instruction & 0x000F); //Dxyn
            break;
        case 0xE000 :
            switch (instruction & 0x00FF) {
                case 0x009E :
                    SKP_Vx(processor, (instruction & 0x0F00)>>8); //Ex9E
                    break;
                case 0x00A1 :
                    SKNP_Vx(processor, (instruction & 0x0F00)>>8); //ExA1
                    break;
            }
            break;
        case 0xF000 :
            switch (instruction & 0x00FF) {
                case 0x0007 :
                    LD_Vx_DT(processor, (instruction & 0x0F00)>>8); //Fx07
                    break;
                case 0x000A :
                    LD_Vx_K(processor, (instruction & 0x0F00)>>8); //Fx0A
                    break;
                case 0x0015 :
                    LD_DT_Vx(processor, (instruction & 0x0F00)>>8); //Fx15
                    break;
                case 0x0018 :
                    LD_ST_Vx(processor, (instruction & 0x0F00)>>8); //Fx18
                    break;
                case 0x001E :
                    ADD_I_Vx(processor, (instruction & 0x0F00)>>8); //Fx1E
                    break;
                case 0x0029 :
                    LD_F_Vx(processor, (instruction & 0x0F00)>>8); //Fx29
                    break;
                case 0x0033 :
                    LD_B_Vx(processor, (instruction & 0x0F00)>>8); //Fx33
                    break;
                case 0x0055 :
                    LD_I_Vx(processor, (instruction & 0x0F00)>>8); //Fx55
                    break;
                case 0x0065 :
                    LD_Vx_I(processor, (instruction & 0x0F00)>>8); //Fx65
                    break;
            }
            break;
    }
}
//------------------------------------------------------
//-----------------Instructions-------------------------
//------------------------------------------------------

void CLS(Cpu *processor) {
    assert(processor);
    Display_CLS(processor->display);
}

void RET(Cpu *processor) {
    assert(processor);
    processor->PC = processor->stack[processor->SP];
    processor->SP--;
}

void JP_addr(Cpu *processor, uint16_t addr) {
    assert(processor);
    processor->PC = addr;
}

void CALL_addr(Cpu *processor, uint16_t addr) {
    assert(processor);
    processor->SP++;
    processor->stack[processor->SP] = processor->PC;
    processor->PC = addr;
}

void SE_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte) {
    assert(processor);
    if (processor->V[x] == byte)
        processor->PC += 2;
}

void SNE_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte) {
    assert(processor);
    if (processor->V[x] != byte)
        processor->PC += 2;
}

void SE_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    if (processor->V[x] == processor->V[y])
        processor->PC += 2;
}

void LD_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte) {
    assert(processor);
    processor->V[x] = byte;
}

void ADD_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte) {
    assert(processor);
    processor->V[x] += byte;
}

void LD_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    processor->V[x] = processor->V[y];
}

void OR_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    processor->V[x] = processor->V[x] | processor->V[y];
    processor->V[0xF] = 0;
}

void AND_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    processor->V[x] = processor->V[x] & processor->V[y];
    processor->V[0xF] = 0;
}

void XOR_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    processor->V[x] = processor->V[x] ^ processor->V[y];
    processor->V[0xF] = 0;
}

void ADD_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    uint16_t temp = processor->V[x] + processor->V[y];
    processor->V[x] = temp & 0xFF;
    if (temp > 255)
        processor->V[0xF] = 1;
    else
        processor->V[0xF] = 0;
}

void SUB_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    uint8_t flag;
    if (processor->V[x] >= processor->V[y])
        flag = 1;
    else
        flag = 0;
    processor->V[x] -= processor->V[y];
    processor->V[0xF] = flag;
}

void SHR_Vx(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    uint8_t flag = processor->V[y] & 0x1;
    processor->V[x] = processor->V[y] >> 1;
    processor->V[0xF] = flag;
}

void SUBN_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    uint8_t flag;
    if (processor->V[x] <= processor->V[y])
        flag = 1;
    else
        flag = 0;
    processor->V[x] = processor->V[y] - processor->V[x];
    processor->V[0xF] = flag;
}

void SHL_Vx(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    uint8_t flag = (processor->V[y] & 0x80) != 0;
    processor->V[x] = processor->V[y] << 1;
    processor->V[0xF] = flag;
}

void SNE_Vx_Vy(Cpu *processor, uint8_t x, uint8_t y) {
    assert(processor);
    if (processor->V[x] != processor->V[y])
        processor->PC += 2;
}

void LD_I_addr(Cpu *processor, uint16_t addr) {
    assert(processor);
    processor->I = addr;
}

void JP_V0_addr(Cpu *processor, uint16_t addr) {
    assert(processor);
    processor->PC = processor->V[0] + addr;
}

void RND_Vx_byte(Cpu *processor, uint8_t x, uint8_t byte) { //    !!! APPELER SRAND() POUR INITIALISER RAND() !!!
    assert(processor);
    processor->V[x] = (rand() % 256) & byte;
}

void DRW_Vx_Vy_nibble(Cpu *processor, uint8_t x, uint8_t y, uint8_t nibble) {
    assert(processor);
    struct Sprite sprite;
    uint8_t line;
    Sprite_init(&sprite, nibble);
    for (uint8_t count = 0; count < nibble; count++) {
        line = Ram_read(processor->memory, processor->I + count);
        Sprite_add(&sprite, line);
    }
    Display_DRW(processor->display, &sprite, processor->V[x], processor->V[y], &processor->V[0xF]);
    Sprite_destroy(&sprite);
}

void SKP_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    if (Keyboard_get(processor->keyboard, processor->V[x])) {
        processor->PC += 2;
    }
}

void SKNP_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    if (!Keyboard_get(processor->keyboard, processor->V[x])) {
        processor->PC += 2;
    }
}

void LD_Vx_DT(Cpu *processor, uint8_t x) {
    assert(processor);
    processor->V[x] = processor->DT;
}

void LD_Vx_K(Cpu *processor, uint8_t x) {
    assert(processor);
    Keyboard_wait(processor->keyboard, &processor->V[x]);
}

void LD_DT_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    processor->DT = processor->V[x];
}

void LD_ST_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    processor->ST = processor->V[x];
}

void ADD_I_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    processor->I += processor->V[x];
}

void LD_F_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    processor->I = 5 * x;
}

void LD_B_Vx(Cpu *processor, uint8_t x) {
    assert(processor);
    uint8_t value = processor->V[x];

    Ram_write(processor->memory, processor->I, value / 100);
    Ram_write(processor->memory, processor->I + 1, value % 100 / 10);
    Ram_write(processor->memory, processor->I + 2, value % 10);
}

void LD_I_Vx(Cpu *processor, uint8_t x) {
    uint8_t counter;
    for (counter = 0; counter <= x; counter++) {
        Ram_write(processor->memory, processor->I + counter, processor->V[counter]);
    }
    processor->I++;
}

void LD_Vx_I(Cpu *processor, uint8_t x) {
    uint8_t counter;
    for (counter = 0; counter <= x; counter++) {
        processor->V[counter] = Ram_read(processor->memory, processor->I + counter);
    }
    processor->I++;
}