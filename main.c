#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "cpu.h"
#include "machine.h"

int main() {

    Machine* machine = Machine_init();

    printf("%d", readRAM(machine->ram,0x50));

    return 0;
}