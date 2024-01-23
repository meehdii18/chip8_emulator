#include "machine.h"

void Load_sprite(Processor *cpu) {
    //0
    writeRAM(cpu->ram, 0, 0xF0);
    writeRAM(cpu->ram, 1, 0x90);
    writeRAM(cpu->ram, 2, 0x90);
    writeRAM(cpu->ram, 3, 0x90);
    writeRAM(cpu->ram, 4, 0xF0);

    //1
    writeRAM(cpu->ram, 5, 0x20);
    writeRAM(cpu->ram, 6, 0x60);
    writeRAM(cpu->ram, 7, 0x20);
    writeRAM(cpu->ram, 8, 0x20);
    writeRAM(cpu->ram, 9, 0x70);

    //2
    writeRAM(cpu->ram, 10, 0xF0);
    writeRAM(cpu->ram, 11, 0x10);
    writeRAM(cpu->ram, 12, 0xF0);
    writeRAM(cpu->ram, 13, 0x80);
    writeRAM(cpu->ram, 14, 0xF0);

    //3
    writeRAM(cpu->ram, 15, 0xF0);
    writeRAM(cpu->ram, 16, 0x10);
    writeRAM(cpu->ram, 17, 0xF0);
    writeRAM(cpu->ram, 18, 0x10);
    writeRAM(cpu->ram, 19, 0xF0);

    //4
    writeRAM(cpu->ram, 20, 0x90);
    writeRAM(cpu->ram, 21, 0x90);
    writeRAM(cpu->ram, 22, 0xF0);
    writeRAM(cpu->ram, 23, 0x10);
    writeRAM(cpu->ram, 24, 0x10);

    //5
    writeRAM(cpu->ram, 25, 0xF0);
    writeRAM(cpu->ram, 26, 0x80);
    writeRAM(cpu->ram, 27, 0xF0);
    writeRAM(cpu->ram, 28, 0x10);
    writeRAM(cpu->ram, 29, 0xF0);

    //6
    writeRAM(cpu->ram, 30, 0xF0);
    writeRAM(cpu->ram, 31, 0x80);
    writeRAM(cpu->ram, 32, 0xF0);
    writeRAM(cpu->ram, 33, 0x90);
    writeRAM(cpu->ram, 34, 0xF0);

    //7
    writeRAM(cpu->ram, 35, 0xF0);
    writeRAM(cpu->ram, 36, 0x10);
    writeRAM(cpu->ram, 37, 0x20);
    writeRAM(cpu->ram, 38, 0x40);
    writeRAM(cpu->ram, 39, 0x40);

    //8
    writeRAM(cpu->ram, 40, 0xF0);
    writeRAM(cpu->ram, 41, 0x90);
    writeRAM(cpu->ram, 42, 0xF0);
    writeRAM(cpu->ram, 43, 0x90);
    writeRAM(cpu->ram, 44, 0xF0);

    //9
    writeRAM(cpu->ram, 45, 0xF0);
    writeRAM(cpu->ram, 46, 0x90);
    writeRAM(cpu->ram, 47, 0xF0);
    writeRAM(cpu->ram, 48, 0x10);
    writeRAM(cpu->ram, 49, 0xF0);

    //A
    writeRAM(cpu->ram, 50, 0xF0);
    writeRAM(cpu->ram, 51, 0x90);
    writeRAM(cpu->ram, 52, 0xF0);
    writeRAM(cpu->ram, 53, 0x90);
    writeRAM(cpu->ram, 54, 0x90);

    //B
    writeRAM(cpu->ram, 55, 0xE0);
    writeRAM(cpu->ram, 56, 0x90);
    writeRAM(cpu->ram, 57, 0xE0);
    writeRAM(cpu->ram, 58, 0x90);
    writeRAM(cpu->ram, 59, 0xE0);

    //C
    writeRAM(cpu->ram, 60, 0xF0);
    writeRAM(cpu->ram, 61, 0x80);
    writeRAM(cpu->ram, 62, 0x80);
    writeRAM(cpu->ram, 63, 0x80);
    writeRAM(cpu->ram, 64, 0xF0);

    //D
    writeRAM(cpu->ram, 65, 0xE0);
    writeRAM(cpu->ram, 66, 0x90);
    writeRAM(cpu->ram, 67, 0x90);
    writeRAM(cpu->ram, 68, 0x90);
    writeRAM(cpu->ram, 69,0xE0);

    //C
    writeRAM(cpu->ram, 70, 0xF0);
    writeRAM(cpu->ram, 71, 0x80);
    writeRAM(cpu->ram, 72, 0x80);
    writeRAM(cpu->ram, 73, 0x80);
    writeRAM(cpu->ram, 74, 0xF0);

    //D
    writeRAM(cpu->ram, 75, 0xE0);
    writeRAM(cpu->ram, 76, 0x90);
    writeRAM(cpu->ram, 77, 0x90);
    writeRAM(cpu->ram, 78, 0x90);
    writeRAM(cpu->ram, 79, 0xE0);

    //E
    writeRAM(cpu->ram, 80, 0xF0);
    writeRAM(cpu->ram, 81, 0x80);
    writeRAM(cpu->ram, 82, 0xF0);
    writeRAM(cpu->ram, 83, 0x80);
    writeRAM(cpu->ram, 84, 0xF0);

    //F
    writeRAM(cpu->ram, 85, 0xF0);
    writeRAM(cpu->ram, 86, 0x80);
    writeRAM(cpu->ram, 87, 0xF0);
    writeRAM(cpu->ram, 88, 0x80);
    writeRAM(cpu->ram, 89, 0x80);
}

Machine* Machine_init(){
    RAM* ram;
    ram = newRAM();
    Processor* cpu;
    cpu = newProcessor(ram);
    struct Display *display = malloc(sizeof(struct Display));
    Display_init(display,10);
    struct Keyboard *keyboard = malloc(sizeof(struct Keyboard));
    Keyboard_init(keyboard);
    struct Speaker* speaker = malloc(sizeof(struct Speaker));
    Speaker_init(speaker);

    Machine *machine = malloc(sizeof(Machine));
    if (machine == NULL){
        fprintf(stderr, "Error : CHIP8 emulator creation failed.\n");
        return NULL;
    }

    machine->cpu = cpu;
    machine->ram = ram;
    machine->display = display;
    machine->keyboard = keyboard;
    machine->speaker = speaker;

    Load_sprite(machine->cpu);

    return machine;
}

void Machine_destroy(Machine* machine){
    deleteProcessor(machine->cpu);
    deleteRAM(machine->ram);
    free(machine->display);
    free(machine->keyboard);
    free(machine->speaker);
}


int Machine_load(Machine* machine,const char* rompath){
    printf("Loading ROM from : %s\n", rompath);
    FILE* file = fopen(rompath,"rb");
    if(file==NULL){
        fprintf(stderr,"Error : reading rom file.\n");
        return 0;
    }

    int address = 0x200;
    uint8_t buffer;
    while (fread(&buffer, sizeof(uint8_t), 1, file) == 1) {
        if (address >= 4095) {
            fprintf(stderr, "Error : memory writing because of the RAM size.\n");
            fclose(file);
            return 0;
        }
        writeRAM(machine->ram, address++, buffer);
    }

    if (ferror(file)) {
        fprintf(stderr, "Error : reading and writing the rom to the memory.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

void Machine_loop(Machine* machine){
    Uint64 lastFetchDecodeExecuteTime = 0, lastDisplayTimersTime = 0;
    const Uint32 interval500 = 1000 / 600; // 600Hz
    const Uint32 intervall60 = 1000 / 60;  // 60Hz
    int stage = 0;

    while (1) {
        fetch_decode_execute(machine->cpu, machine->display, machine->keyboard);
        SDL_Delay(stage ? 1 : 2);
        stage = !stage;

        Uint64 currentTime = SDL_GetTicks64();
        if (currentTime - lastDisplayTimersTime > intervall60) {
            Display_update(machine->display);
            decrement_timers(machine->cpu,machine->speaker);
            lastDisplayTimersTime = currentTime;
        }
    }
}

