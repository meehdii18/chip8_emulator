#include "machine.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
        errcode = SDL;
    }
    Machine* machine = Machine_init();
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/1-chip8-logo.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/2-ibm-logo.ch8");
    Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/3-corax+.ch8");
    Machine_loop(machine);


    return 0;
}