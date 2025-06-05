#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <stdio.h>
#include "texture.h"

GLuint wallTexture, floorTexture, ceilingTexture, alloutsideTexture, guideTexture, duckTexture;

GLuint loadTexture(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (!image) {
        printf("Image load error: %s\n", IMG_GetError());
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(image);
    return textureID;
}

void load_all_textures() {
    wallTexture = loadTexture("textures/Subtle-Plaster.jpg");
    floorTexture = loadTexture("textures/Mosaic-small.jpg");
    ceilingTexture = loadTexture("textures/Cracked-paint.jpg");
    alloutsideTexture = loadTexture("textures/Color-white.jpg");
    guideTexture = loadTexture("textures/Guide.jpg");
    duckTexture = loadTexture("textures/duck.jpg");
}
