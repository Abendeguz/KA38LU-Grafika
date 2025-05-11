#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// Ablakméret
#define WIDTH 800
#define HEIGHT 600

SDL_Window* window = NULL;
SDL_GLContext glContext;
GLuint wallTexture, floorTexture, ceilingTexture, alloutsideTexture;

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 6.0f; 
int lastMouseX, lastMouseY;
float circleX = 0.0f;
float circleZ = 0.0f;

GLuint loadTexture(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (!image) {
        printf("Hiba a kép betöltésekor: %s\n", IMG_GetError());
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

// Inicializálás
int init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL inicializálási hiba: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        printf("SDL_image init hiba: %s\n", IMG_GetError());
        return 0;
    }

    // SDL ablak létrehozása OpenGL támogatással
    window = SDL_CreateWindow("3D Kocka - OpenGL SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Ablak hiba: %s\n", SDL_GetError());
        return 0;
    }

    // OpenGL kontextus létrehozása
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("OpenGL kontextus hiba: %s\n", SDL_GetError());
        return 0;
    }

    // Alap OpenGL beállítások
    glEnable(GL_DEPTH_TEST); // Mélységi teszt bekapcsolása
    glEnable(GL_TEXTURE_2D);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(window, SDL_TRUE);

    // Perspektivikus vetítés beállítása
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WIDTH / (double)HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    wallTexture = loadTexture("Subtle-Plaster.jpg");
    floorTexture = loadTexture("Mosaic-small.jpg");
    ceilingTexture = loadTexture("Cracked-paint.jpg");
    alloutsideTexture = loadTexture("Color-white.jpg");
    return 1;
}

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


// Kocka kirajzolása
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
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.01f, -1.5f,  1.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.01f, -1.5f, -1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.01f,  1.5f, -1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.01f,  1.5f,  1.5f);

// Külső jobb fal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.01f, -2.0f, -1.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.01f, -1.5f,  1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.01f,  1.5f,  1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.01f,  1.5f, -1.5f);

// Külső plafon
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, 1.01f, -1.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f, 1.01f, -1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f, 1.01f,  1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, 1.01f,  1.5f);

// Külső padló
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -1.001f, -1.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -1.001f,  1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f, -1.001f,  1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.5f, -1.001f, -1.5f);
    glEnd();


}

// Kirajzolás
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera pozíció
    gluLookAt(cameraX, cameraY, cameraZ, 
        0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f);
    // Kocka forgatása
    //glPushMatrix();
    //glRotatef(angle, 1.0f, 1.0f, 0.0f);
    drawCube();
    //glPopMatrix();
    drawCircleOnCeiling(circleX, circleZ, 0.1f, 32);

    SDL_GL_SwapWindow(window);
}

// Főprogram
int main(int argc, char* argv[]) {
    if (!init()) {
        return -1;
    }

    //int zoomspeed;
    int running = 1;
    SDL_Event event;

    // Főciklus
    while (running) {
        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        if (keystates[SDL_SCANCODE_UP]) {
            cameraZ -= 0.05f; 
        }
        if (keystates[SDL_SCANCODE_DOWN]) {
            cameraZ += 0.05f; 
        }


        // Korlátok: min. 3.0, max. 10.0
        if (cameraZ < 3.0f) cameraZ = 3.0f;
        if (cameraZ > 10.0f) cameraZ = 10.0f;

        // Kör mozgatása
        if (keystates[SDL_SCANCODE_W]) {
            circleZ -= 0.05f;
        }
        if (keystates[SDL_SCANCODE_S]) {
            circleZ += 0.05f;
        }
        if (keystates[SDL_SCANCODE_A]) {
            circleX -= 0.05f;
        }
        if (keystates[SDL_SCANCODE_D]) {
            circleX += 0.05f;
        }
        
        // Korlátozás kör
        if (circleX < -1.9f) circleX = -1.9f;
        if (circleX >  1.9f) circleX =  1.9f;
        if (circleZ < -0.9f) circleZ = -0.9f;
        if (circleZ >  0.9f) circleZ =  0.9f;


        if (keystates[SDL_SCANCODE_L]) {
            running = 0;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEMOTION) {
                cameraX += event.motion.xrel * 0.01f;
                cameraY -= event.motion.yrel * 0.01f;

                if (cameraX > 3.0f) cameraX = 3.0f;
                if (cameraX < -3.0f) cameraX = -3.0f;
                if (cameraY > 2.0f) cameraY = 2.0f;
                if (cameraY < -2.0f) cameraY = -2.0f;
            } 
        }

        //angle += 0.5f; // Forgatás növelése
        render();
        SDL_Delay(16); // Kis késleltetés (~60 FPS)
    }

    // Erőforrások felszabadítása
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
