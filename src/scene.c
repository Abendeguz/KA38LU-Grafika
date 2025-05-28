#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/camera.h"
#include "../include/texture.h"
#include "scene.h"

extern SDL_Window* window;

float circleX = 0.0f, circleZ = 0.0f;


void drawCircleOnCeiling(float x, float z, float radius, int segments) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, 0.999f, z);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float dx = cos(angle) * radius;
        float dz = sin(angle) * radius;
        glVertex3f(x + dx, 0.999f, z + dz);
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    
}

void drawCube() {

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    // Hátsó oldal 
    
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-2.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.0f);

    // Bal oldal 
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -1.0f);

    // Jobb oldal 
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, -1.0f,  1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, ceilingTexture);
    glBegin(GL_QUADS);

    // Teteje 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -1.0f);
    glEnd();
    // Alja

    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, -1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, -1.0f,  1.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, alloutsideTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f, -1.0f, -1.01f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, -1.0f, -1.01f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f,  1.0f, -1.01f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f,  1.0f, -1.01f);

// Külső bal fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.01f, -1.05f,  1.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.01f, -1.05f, -1.05f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.01f,  1.05f, -1.05f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.01f,  1.05f,  1.05f);

// Külső jobb fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.01f, -1.05f, -1.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.01f, -1.05f,  1.05f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.01f,  1.05f,  1.05f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.01f,  1.05f, -1.05f);

// Külső plafon
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.05f, 1.01f, -1.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.05f, 1.01f, -1.05f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.05f, 1.01f,  1.05f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.05f, 1.01f,  1.05f);

// Külső padló
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.05f, -1.001f, -1.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.05f, -1.001f,  1.05f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.05f, -1.001f,  1.05f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.05f, -1.001f, -1.05f);
    glEnd();


}

void main_loop() {
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEMOTION) {
                handle_mouse_motion(event.motion.xrel, event.motion.yrel);
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        handle_camera_keys(keystates);
        if (keystates[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -cameraZ);
        glRotatef(cameraY, 1.0f, 0.0f, 0.0f);
        glRotatef(cameraX, 0.0f, 1.0f, 0.0f);

        drawCircleOnCeiling(circleX, circleZ, 0.1f, 32);
        drawCube(); // akkor használd, ha már megírtad

        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // kb. 60 FPS
    }
}