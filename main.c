#include "machine.h"

int main(int argc, char** argv) {
    if(argc != 2){
        fprintf(stderr,"Too many or too few arguments\n");
        fprintf(stderr,"Usage: %s <rom_path>\n",argv[0]);
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)) {
        errcode = SDL;
    }else{
        printf("The SDL library has been initialized successfully.\n");
        Machine* machine = Machine_init();
        if(machine){
            printf("The CHIP 8 emulator is ready.\n");
            Machine_load(machine,argv[1]);
            SDL_Event event;
            int running = 1;
            while(running){
                while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        running = 0;
                    }
                }
                Machine_loop(machine);
                if(!running){
                    break;
                }
            }
            Machine_destroy(machine);
        }else{
            fprintf(stderr,"The CHIP 8 has occured a fatal error, please restart the emulator.\n");
            Machine_destroy(machine);
        }
    }
    return 0;
}