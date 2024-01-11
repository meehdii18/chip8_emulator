#include "machine.h"

Machine Machine_init(){
    RAM* ram = newRAM();
    Processor* cpu = newProcessor(ram);
    //struct Display display;
    //Display_init(display);
    //struct Keyboard keyboard;
    //Keyboard_init(keyboard);
    //struct Speaker* speaker;
    //Speaker_init(speaker);

    Machine machine;
    machine.cpu = cpu;
    machine.ram = ram;
    //machine.display = display;
    //machine.keyboard = keyboard;
    //machine.speaker = speaker;
}

void Machine_load(Machine machine,const char* rom){
    // charger dans la ram une rom à partir de 0x200
}

void Machine_loop(Machine machine){
    // call fetch decode execute (cpu) @500Hz
    // call update (display) @30hz or @60Hz
    // call decrement_timers (cpu) @60hz
}