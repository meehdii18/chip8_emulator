#include "ram.h"


Ram *Ram_new(void) {
    Ram *newRam = malloc(sizeof(Ram));
    Ram_init(newRam);

    return newRam;
}

void Ram_init(Ram *memory) {
    assert(memory);
    memory->tab = calloc(0x1000, sizeof(int8_t));
}

void Ram_delete(Ram *memory) {
    assert(memory);
    Ram_destroy(memory);
    free(memory);
}

void Ram_destroy(Ram *memory) {
    assert(memory);
    free(memory->tab);
}

void Ram_write(Ram *memory, uint16_t address, uint8_t value) {
    assert(memory);
    if (address < 0x1000) {
        memory->tab[address] = value;
    } else {
        fprintf(stderr, "Error : Can't write in memory.\n");
        exit(EXIT_FAILURE);
    }
}

uint8_t Ram_read(Ram *memory, uint16_t address) {
    assert(memory);
    if (address <= 0x1000)
        return memory->tab[address];
    else {
        printf("%x",address);
        fprintf(stderr, "Error : Can't read in memory.");
        exit(EXIT_FAILURE);
    }
}