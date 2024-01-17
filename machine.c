#include "machine.h"

void Load_sprite(Processor *cpu) {
    //0
    writeRAM(cpu->ram, 0, 0xF0);
    writeRAM(cpu->ram, 2, 0x90);
    writeRAM(cpu->ram, 4, 0x90);
    writeRAM(cpu->ram, 6, 0x90);
    writeRAM(cpu->ram, 8, 0xF0);

    //1
    writeRAM(cpu->ram, 10, 0x20);
    writeRAM(cpu->ram, 12, 0x60);
    writeRAM(cpu->ram, 14, 0x20);
    writeRAM(cpu->ram, 16, 0x20);
    writeRAM(cpu->ram, 18, 0x70);

    //2
    writeRAM(cpu->ram, 20, 0xF0);
    writeRAM(cpu->ram, 22, 0x10);
    writeRAM(cpu->ram, 24, 0xF0);
    writeRAM(cpu->ram, 26, 0x80);
    writeRAM(cpu->ram, 28, 0xF0);

    //3
    writeRAM(cpu->ram, 30, 0xF0);
    writeRAM(cpu->ram, 32, 0x10);
    writeRAM(cpu->ram, 34, 0xF0);
    writeRAM(cpu->ram, 36, 0x10);
    writeRAM(cpu->ram, 38, 0xF0);

    //4
    writeRAM(cpu->ram, 40, 0x90);
    writeRAM(cpu->ram, 42, 0x90);
    writeRAM(cpu->ram, 44, 0xF0);
    writeRAM(cpu->ram, 46, 0x10);
    writeRAM(cpu->ram, 48, 0x10);

    //5
    writeRAM(cpu->ram, 50, 0xF0);
    writeRAM(cpu->ram, 52, 0x80);
    writeRAM(cpu->ram, 54, 0xF0);
    writeRAM(cpu->ram, 56, 0x10);
    writeRAM(cpu->ram, 58, 0xF0);

    //6
    writeRAM(cpu->ram, 60, 0xF0);
    writeRAM(cpu->ram, 62, 0x80);
    writeRAM(cpu->ram, 64, 0xF0);
    writeRAM(cpu->ram, 66, 0x90);
    writeRAM(cpu->ram, 68, 0xF0);

    //7
    writeRAM(cpu->ram, 70, 0xF0);
    writeRAM(cpu->ram, 72, 0x10);
    writeRAM(cpu->ram, 74, 0x20);
    writeRAM(cpu->ram, 76, 0x40);
    writeRAM(cpu->ram, 78, 0x40);

    //8
    writeRAM(cpu->ram, 80, 0xF0);
    writeRAM(cpu->ram, 82, 0x90);
    writeRAM(cpu->ram, 84, 0xF0);
    writeRAM(cpu->ram, 86, 0x90);
    writeRAM(cpu->ram, 88, 0xF0);

    //9
    writeRAM(cpu->ram, 90, 0xF0);
    writeRAM(cpu->ram, 92, 0x90);
    writeRAM(cpu->ram, 94, 0xF0);
    writeRAM(cpu->ram, 96, 0x10);
    writeRAM(cpu->ram, 98, 0xF0);

    //A
    writeRAM(cpu->ram, 100, 0xF0);
    writeRAM(cpu->ram, 102, 0x90);
    writeRAM(cpu->ram, 104, 0xF0);
    writeRAM(cpu->ram, 106, 0x90);
    writeRAM(cpu->ram, 108, 0x90);

    //B
    writeRAM(cpu->ram, 110, 0xE0);
    writeRAM(cpu->ram, 112, 0x90);
    writeRAM(cpu->ram, 114, 0xE0);
    writeRAM(cpu->ram, 116, 0x90);
    writeRAM(cpu->ram, 118, 0xE0);

    //C
    writeRAM(cpu->ram, 120, 0xF0);
    writeRAM(cpu->ram, 122, 0x80);
    writeRAM(cpu->ram, 124, 0x80);
    writeRAM(cpu->ram, 126, 0x80);
    writeRAM(cpu->ram, 128, 0xF0);

    //D
    writeRAM(cpu->ram, 130, 0xE0);
    writeRAM(cpu->ram, 132, 0x90);
    writeRAM(cpu->ram, 134, 0x90);
    writeRAM(cpu->ram, 136, 0x90);
    writeRAM(cpu->ram, 138, 0xE0);

    //E
    writeRAM(cpu->ram, 140, 0xF0);
    writeRAM(cpu->ram, 142, 0x80);
    writeRAM(cpu->ram, 144, 0xF0);
    writeRAM(cpu->ram, 146, 0x80);
    writeRAM(cpu->ram, 148, 0xF0);

    //F
    writeRAM(cpu->ram, 150, 0xF0);
    writeRAM(cpu->ram, 152, 0x80);
    writeRAM(cpu->ram, 154, 0xF0);
    writeRAM(cpu->ram, 156, 0x80);
    writeRAM(cpu->ram, 158, 0x80);
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
        fprintf(stderr,"Erreur de lecture du fichier rom.");
        return 0;
    }

    int address = 0x200;
    uint8_t buffer;
    while (fread(&buffer, sizeof(uint8_t), 1, file) == 1) {
        if (address >= 4095) {
            fprintf(stderr, "Erreur d'écriture de la rom à cause de la taille de la RAM");
            fclose(file);
            return 0;
        }
        writeRAM(machine->ram, address++, buffer);
    }

    if (ferror(file)) {
        fprintf(stderr, "Erreur dans la lecture et l'écriture de la rom sur la ram.");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}
void Machine_loop(Machine* machine){
    Uint64 lastFetchDecodeExecuteTime = 0, lastDisplayTimersTime = 0;
    const Uint32 interval500 = 1000 / 500; // 500Hz
    const Uint32 intervall60 = 1000 / 60; // 60Hz

    while (1) {
        Uint64 currentTime = SDL_GetTicks64();
        if (currentTime - lastFetchDecodeExecuteTime > interval500) {
            fetch_decode_execute(machine->cpu, machine->display, machine->keyboard);
            lastFetchDecodeExecuteTime = currentTime;
        }

        if (currentTime - lastDisplayTimersTime > intervall60) {
            Display_update(machine->display);
            decrement_timers(machine->cpu);
            lastDisplayTimersTime = currentTime;
        }
    }
}

