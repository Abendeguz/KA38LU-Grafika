#define SDL_MAIN_HANDLED
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/texture.h"
#include "../include/utils.h"

int main(int argc, char* argv[]) {
    if (!init_app()) return -1;
    
    main_loop();

    cleanup();
    return 0;
}
