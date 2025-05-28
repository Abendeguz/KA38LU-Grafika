#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

extern float cameraX, cameraY, cameraZ;

void handle_mouse_motion(int xrel, int yrel);
void handle_camera_keys(const Uint8* keystates);

#endif
