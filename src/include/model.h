#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "definitions.h"

struct Vertex
{
    float x;
    float y;
    float z;
};

struct Triangle
{
    int a;
    int b;
    int c;
};

struct color
{
    float r;
    float g;
    float b;
    float a;
};


struct Model
{
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
};

#endif // MODEL_H