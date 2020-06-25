#ifndef MESH_H
#define MESH_H

#include "renderer/triangle.hpp"

#include <vector>

class Mesh
{
    public:
        Mesh(std::vector<Triangle> triangles = {});

        std::vector<Triangle> triangles;

        void addTriangle(Triangle triangle);
        void scale(double factor);
        
        static Mesh cube(void);
};


#endif // MESH_H