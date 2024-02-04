#include "machine.h"


Machine *Machine_new(void) {

    Machine *machine = malloc(sizeof(Machine));
    Machine_init(machine);

    return machine;
}

void Machine_init(Machine *machine) {

    machine->memory = Ram_new();

    machine->display = malloc(sizeof(struct Display));

    machine->keyboard = malloc(sizeof(struct Keyboard));

    machine->speaker = malloc(sizeof(struct Speaker));

    Display_init(machine->display, 20);

    Keyboard_init(machine->keyboard);

    Speaker_init(machine->speaker);

    machine->processor = Cpu_new();

    machine->processor->memory = machine->memory;

    machine->processor->display = machine->display;

    machine->processor->keyboard = machine->keyboard;

    machine->processor->speaker = machine->speaker;

    uint8_t hexdigits[16][5] = {{0xF0, 0x90, 0x90, 0x90, 0xF0},
                                {0x20, 0x60, 0x20, 0x20, 0x70},
                                {0xF0, 0x10, 0xF0, 0x80, 0xF0},
                                {0xF0, 0x10, 0xF0, 0x10, 0xF0},
                                {0x90, 0x90, 0xF0, 0x10, 0x10},
                                {0xF0, 0x80, 0xF0, 0x10, 0xF0},
                                {0xF0, 0x80, 0xF0, 0x90, 0xF0},
                                {0xF0, 0x10, 0x20, 0x40, 0x40},
                                {0xF0, 0x90, 0xF0, 0x90, 0xF0},
                                {0xF0, 0x90, 0xF0, 0x10, 0xF0},
                                {0xF0, 0x90, 0xF0, 0x90, 0x90},
                                {0xE0, 0x90, 0xE0, 0x90, 0xE0},
                                {0xF0, 0x80, 0x80, 0x80, 0xF0},
                                {0xE0, 0x90, 0x90, 0x90, 0xE0},
                                {0xF0, 0x80, 0xF0, 0x80, 0xF0},
                                {0xF0, 0x80, 0xF0, 0x80, 0x80}};

    for (uint8_t digit = 0; digit <= 15; digit++) {
        for (uint8_t line = 0; line <= 4; line++) {
            Ram_write(machine->memory, digit * 5 + line, hexdigits[digit][line]);
        }
    }
}

void Machine_delete(Machine *machine) {
    assert(machine);
    Machine_destroy(machine);
    Cpu_delete(machine->processor);
    Ram_delete(machine->memory);
    Display_destroy(machine->display);
    Keyboard_destroy(machine->keyboard);
    Speaker_destroy(machine->speaker);
    free(machine);
}

void Machine_destroy(Machine *machine) {
    assert(machine);
    Cpu_destroy(machine->processor);
}

void Machine_load(Machine *machine, char *rom_file) {

    assert(machine);
    assert(rom_file);

    printf("Loading ROM from %s\n",rom_file);

    FILE *rom = fopen(rom_file, "rb");

    if (rom == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier donné en lecture\n");
        exit(1);
    }

    uint16_t address = 0x200;

    uint8_t buffer;
    while (fread(&buffer, sizeof(uint8_t), 1, rom) == 1) {
        Ram_write(machine->memory, address++, buffer);
    }

    fclose(rom);
}

void Machine_run(Machine *machine) {
    SDL_Event event;
    Uint64 last_60 = 0;
    Uint32 interval60 = 1000 / 60;
    uint8_t stage = 0;
    uint8_t running = 1;

    while (running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        Uint64 current_time = SDL_GetTicks64();
        uint8_t decrement = (current_time - last_60) / interval60;
        if (decrement >= 1) {
            Display_update(machine->display);
            if (machine->processor->ST > 0) {
                Speaker_on(machine->speaker);
                if (decrement > machine->processor->ST) {
                    machine->processor->ST = 0;
                } else {
                machine->processor->ST-= decrement;
                }
            } else {
                Speaker_off(machine->speaker);
            }
            if (machine->processor->DT > 0) {
                if (decrement > machine->processor->DT) {
                    machine->processor->DT = 0;
                } else {
                machine->processor->DT-= decrement;
                }
            }
            last_60 = current_time;
        }

        SDL_Delay(stage ? 1 : 2);
        stage = !stage;
        fetch_decode_execute(machine->processor);

    }
}



