#include "machine.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
        errcode = SDL;
    }
    Machine* machine = Machine_init();
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/1-chip8-logo.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/2-ibm-logo.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/3-corax+.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/4-flags.ch8");
    Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/5-quirks.ch8");
    writeRAM(machine->ram,0x1FF,1);
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/6-keypad.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/7-beep.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/8-scrolling.ch8");

    Machine_loop(machine);


    return 0;
}