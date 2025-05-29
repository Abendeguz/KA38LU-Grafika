#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/texture.h"
#include "../include/utils.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

SDL_Window* window = NULL;
SDL_GLContext glContext;

SDL_Window* get_window() { return window; }

int init_app() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init error: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        printf("SDL_image init error: %s\n", IMG_GetError());
        return 0;
    }

    window = SDL_CreateWindow("3D Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 0;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("OpenGL context error: %s\n", SDL_GetError());
        return 0;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // Teljes sötétség, csak a fény világítson
    GLfloat ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // ez lehet később sötétebb is, ha kell
    

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(window, SDL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    load_all_textures();

    return 1;
}

void cleanup() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
