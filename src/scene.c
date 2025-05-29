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
    glVertex3f(x, 9.999f, z);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float dx = cos(angle) * radius;
        float dz = sin(angle) * radius;
        glVertex3f(x + dx, 9.999f, z + dz);
    }
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    
}


void drawCube() {
    GLfloat mat_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat mat_shininess[] = {32.0f};
    float SCALE = 10.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // Hátsó oldal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-2.0f * SCALE, -1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(0.0f, 1.0f);  glVertex3f(-2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(1.0f, 1.0f);  glVertex3f( 2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(1.0f, 0.0f);  glVertex3f( 2.0f * SCALE, -1.0f * SCALE, -1.0f * SCALE);

    // Bal oldal
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-2.0f * SCALE, -1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(1.0f, 0.0f);  glVertex3f(-2.0f * SCALE, -1.0f * SCALE,  1.0f * SCALE);
    glTexCoord2f(1.0f, 1.0f);  glVertex3f(-2.0f * SCALE,  1.0f * SCALE,  1.0f * SCALE);
    glTexCoord2f(0.0f, 1.0f);  glVertex3f(-2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);

    // Jobb oldal
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f( 2.0f * SCALE, -1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(0.0f, 1.0f);  glVertex3f( 2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(1.0f, 1.0f);  glVertex3f( 2.0f * SCALE,  1.0f * SCALE,  1.0f * SCALE);
    glTexCoord2f(1.0f, 0.0f);  glVertex3f( 2.0f * SCALE, -1.0f * SCALE,  1.0f * SCALE);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, ceilingTexture);
    glBegin(GL_QUADS);

    // Teteje
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);  glVertex3f(-2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);
    glTexCoord2f(1.0f, 0.0f);  glVertex3f(-2.0f * SCALE,  1.0f * SCALE,  1.0f * SCALE);
    glTexCoord2f(1.0f, 1.0f);  glVertex3f( 2.0f * SCALE,  1.0f * SCALE,  1.0f * SCALE);
    glTexCoord2f(0.0f, 1.0f);  glVertex3f( 2.0f * SCALE,  1.0f * SCALE, -1.0f * SCALE);
    glEnd();

    // Alja - kis csempékre bontva
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glBegin(GL_QUADS);

    float floorY = -1.0f * SCALE;
    int tileCountX = 100;
    int tileCountZ = 100;
    float startX = -2.0f * SCALE;
    float startZ = -1.0f * SCALE;
    float tileWidth = (4.0f * SCALE) / tileCountX;
    float tileDepth = (2.0f * SCALE) / tileCountZ;

    for (int x = 0; x < tileCountX; x++) {
        for (int z = 0; z < tileCountZ; z++) {
            float x0 = startX + x * tileWidth;
            float z0 = startZ + z * tileDepth;
            float x1 = x0 + tileWidth;
            float z1 = z0 + tileDepth;

            glTexCoord2f(0.0f, 0.0f); glVertex3f(x0, floorY, z0);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, floorY, z0);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, floorY, z1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x0, floorY, z1);
        }
    }
    glEnd();

    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, alloutsideTexture);
    glBegin(GL_QUADS);

    // Hátsó külső fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.0f * SCALE, -1.0f * SCALE, -1.01f * SCALE);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f * SCALE, -1.0f * SCALE, -1.01f * SCALE);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.0f * SCALE,  1.0f * SCALE, -1.01f * SCALE);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.0f * SCALE,  1.0f * SCALE, -1.01f * SCALE);

    // Külső bal fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.01f * SCALE, -1.05f * SCALE,  1.05f * SCALE);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.01f * SCALE, -1.05f * SCALE, -1.05f * SCALE);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.01f * SCALE,  1.05f * SCALE, -1.05f * SCALE);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.01f * SCALE,  1.05f * SCALE,  1.05f * SCALE);

    // Külső jobb fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.01f * SCALE, -1.05f * SCALE, -1.05f * SCALE);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.01f * SCALE, -1.05f * SCALE,  1.05f * SCALE);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.01f * SCALE,  1.05f * SCALE,  1.05f * SCALE);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.01f * SCALE,  1.05f * SCALE, -1.05f * SCALE);

    // Külső plafon
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.05f * SCALE, 1.01f * SCALE, -1.05f * SCALE);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.05f * SCALE, 1.01f * SCALE, -1.05f * SCALE);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.05f * SCALE, 1.01f * SCALE,  1.05f * SCALE);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.05f * SCALE, 1.01f * SCALE,  1.05f * SCALE);

    // Külső padló
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.05f * SCALE, -1.001f * SCALE, -1.05f * SCALE);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.05f * SCALE, -1.001f * SCALE,  1.05f * SCALE);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.05f * SCALE, -1.001f * SCALE,  1.05f * SCALE);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.05f * SCALE, -1.001f * SCALE, -1.05f * SCALE);

    glEnd();


}

void setup_spotlight(float x, float z) {
    GLfloat light_position[] = { x, 1.0f, z, 1.0f };
    GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
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

         // Kör mozgatása
        if (keystates[SDL_SCANCODE_W]) {
            circleZ -= 0.3f;
        }
        if (keystates[SDL_SCANCODE_S]) {
            circleZ += 0.3f;
        }
        if (keystates[SDL_SCANCODE_A]) {
            circleX -= 0.3f;
        }
        if (keystates[SDL_SCANCODE_D]) {
            circleX += 0.3f;
        }
        
        // Korlátozás kör
        
        if (circleX < -19.9f) circleX = -19.9f;
        if (circleX >  19.9f) circleX =  19.9f;
        if (circleZ < -9.9f) circleZ = -9.9f;
        if (circleZ >  9.9f) circleZ =  9.9f;
        
        handle_camera_keys(keystates);
        if (keystates[SDL_SCANCODE_ESCAPE]) {
            running = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -cameraZ);
        glRotatef(cameraY, 1.0f, 0.0f, 0.0f);
        glRotatef(cameraX, 0.0f, 1.0f, 0.0f);

        setup_spotlight(circleX, circleZ);
        drawCircleOnCeiling(circleX, circleZ, 1.0f, 32);
        drawCube();

        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // kb. 60 FPS
    }
}