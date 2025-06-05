#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/camera.h"
#include "../include/texture.h"
#include "scene.h"
#include <obj/draw.h>



extern SDL_Window* window;

float circleX = 0.0f, circleZ = 0.0f;


void init_scene(Scene* scene)
{
    // Betölti a cube modellt (ha kell)
    //load_model(&(scene->cube), "assets/cube.obj"); // opcionális

    // Betölti a cat és duck modelleket
    load_model(&(scene->cat), "assets/cat.obj");
    load_model(&(scene->duck), "assets/duck.obj");

    // Alapértelmezett anyag
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 1000.0;
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}


void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    glEnable(GL_LIGHTING);

    // CAT modellek megjelenítése
    glBindTexture(GL_TEXTURE_2D, ceilingTexture);
    glPushMatrix();
    glTranslatef(-10.0f, -10.0f, 0.0f); // helyezzük el a padlóra
    glScalef(5.5f, 5.5f, 5.5f);
    //glDisable(GL_LIGHT1);
    draw_model(&(scene->cat));
    //glEnable(GL_LIGHT1);
    glPopMatrix();

    // DUCK modellek megjelenítése
    glBindTexture(GL_TEXTURE_2D, duckTexture);

    glPushMatrix();
    glTranslatef(5.0f, -9.9f, 0.0f); // másik sarokba
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
    glScalef(3.5f, 3.5f, 3.5f);
    draw_model(&(scene->duck));
    glPopMatrix();
}

void drawCircleOnCeiling(float x, float z, float radius, int segments) {
    glDisable(GL_LIGHTING);

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
    int tileCountX = 150;
    int tileCountZ = 150;
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

    glBindTexture(GL_TEXTURE_2D, guideTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.05f * SCALE, 1.01f * SCALE,  1.05f * SCALE); // bal alsó
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.05f * SCALE, 1.01f * SCALE,  1.05f * SCALE); // jobb alsó
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.05f * SCALE, 2.5f * SCALE,  1.05f * SCALE); // jobb felső
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.05f * SCALE, 2.5f * SCALE,  1.05f * SCALE); // bal felső

    glEnd();

}

void setup_spotlight(float x, float z) {
    
    // Background light

    float position[] = { 0.0f, 0.0f, -10.0f, 1.0f };
    float ambient_light[] = { 0.0f, 0.0f, 0.1f, 1.0f };
    float diffuse_light[] = { 0.0f, 0.0f, 0.2f, 1.0f };
    float specular_light[] = { 1.f, 1.f, 1.f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    // glDisable(GL_LIGHT0);

    // Spot light

    GLfloat spot_position[] = { x, 1.0f, z, 1.0f };
    GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };
    GLfloat spot_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spot_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spot_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_POSITION, spot_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.f);
    glLightfv(GL_LIGHT1, GL_AMBIENT, spot_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spot_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spot_specular);

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
        
        if (circleX < -19.0f) circleX = -19.0f;
        if (circleX >  19.0f) circleX =  19.0f;
        if (circleZ < -9.0f) circleZ = -9.0f;
        if (circleZ >  9.0f) circleZ =  9.0f;
        
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
        static Scene scene;
        static int scene_initialized = 0;

        if (!scene_initialized) {
        init_scene(&scene);
            scene_initialized = 1;
        }

        // render cube
        drawCube();

        // render models
        render_scene(&scene);

        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // kb. 60 FPS
    }
}