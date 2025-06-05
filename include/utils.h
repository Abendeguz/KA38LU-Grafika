#ifndef UTILS_H
#define UTILS_H


int init_app();
void cleanup();

typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

typedef struct Material
{
    struct Color ambient;
    struct Color diffuse;
    struct Color specular;
    float shininess;
} Material;

#endif
