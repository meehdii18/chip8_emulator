#include "machine.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
        errcode = SDL;
    }
    Machine* machine = Machine_init();
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/1-chip8-logo.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/2-ibm-logo.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/3-corax+.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/4-flags.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/5-quirks.ch8");
    //writeRAM(machine->ram,0x1FF,1);
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/6-keypad.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/7-beep.ch8");
    //Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/test/8-scrolling.ch8");

    Machine_load(machine,"/home/administrateur/CLionProjects/chip8_emulator/rom/games/Worm V4 [RB-Revival Studios, 2007].ch8");

    Machine_loop(machine);


    return 0;
}