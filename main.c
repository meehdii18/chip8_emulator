#include "machine.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Unexpected number of arguments.\n");
        printf("Usage: %s <path_to_rom>\n", argv[0]);
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
        errcode = SDL;
    }
    else {
        printf("The SDL library has been initialized successfully.\n");
        struct Machine* machine = Machine_init();
        if (!machine) {
            printf("The CHIP 8 emulator is ready.\n");
            if (!Machine_load(machine,argv[1])) {
                printf("The ROM <%s> has been loaded.\n",argv[1]);
                printf("Run...\n");
                while (
                        !Machine_loop(machine)
                        );
            }
            Machine_destroy(machine);
        }
        SDL_Quit();
    }
    if (errcode != QUIT) {
        fprintf(stderr,"The program has terminated abnormally (errcode=%s)\n",errorstr());
        return 1;
    }
    return 0;




/*
    if (argc < 2) {
        printf("Usage: %s <path_to_rom>\n", argv[0]);
        return 1;
    }
    printf("%s",argv[1]);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {
        errcode = SDL;
    }
    Machine *machine = Machine_init();

    Machine_load(machine, argv[1]);

    while(!Machine_loop(machine)){
        SDL_Quit();
    }

    return 0;
    */
}