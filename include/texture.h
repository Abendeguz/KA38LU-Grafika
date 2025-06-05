#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

GLuint loadTexture(const char* filename);
extern GLuint wallTexture, floorTexture, ceilingTexture, alloutsideTexture, guideTexture, duckTexture;

void load_all_textures();

#endif
