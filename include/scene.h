#ifndef SCENE_H
#define SCENE_H
#include <obj/load.h>
#include <obj/model.h>
#include "../include/utils.h"

typedef struct Scene
{
    //Model cube;
    Model cat;
    Model duck;
    Material material;
    GLuint texture_id;
} Scene;


void init_scene(Scene* scene);
void set_material(const Material* material);
void render_scene(const Scene* scene);
void drawCube();
void drawCircleOnCeiling(float x, float z, float radius, int segments);
void setup_spotlight(float x, float z);
void main_loop();


#endif
