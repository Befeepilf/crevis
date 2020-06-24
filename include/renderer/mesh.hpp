#ifndef MESH_H
#define MESH_H

#include "renderer/triangle.hpp"

#include <vector>

class Mesh
{
    public:
        explicit Mesh(std::vector<Triangle> triangles = {});
        void addTriangle(Triangle triangle);
        std::vector<Triangle> triangles;
};

#endif // MESH_H