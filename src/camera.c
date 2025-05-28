#include <SDL2/SDL.h>
#include "camera.h"

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 6.0f;

void handle_mouse_motion(int xrel, int yrel) {
    cameraX += xrel * 0.04f;
    cameraY -= yrel * 0.04f;

    if (cameraX > 30.0f) cameraX = 30.0f;
    if (cameraX < -30.0f) cameraX = -30.0f;
    if (cameraY > 30.0f) cameraY = 30.0f;
    if (cameraY < -30.0f) cameraY = -30.0f;
}

void handle_camera_keys(const Uint8* keystates) {
    if (keystates[SDL_SCANCODE_UP]) cameraZ -= 0.05f;
    if (keystates[SDL_SCANCODE_DOWN]) cameraZ += 0.05f;

    if (cameraZ < 3.0f) cameraZ = 3.0f;
    if (cameraZ > 10.0f) cameraZ = 10.0f;
}
