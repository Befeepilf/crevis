#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"

#include <iostream>

Mesh::Mesh(std::vector<Triangle> triangles) : triangles(triangles)
{

}

void Mesh::addTriangle(Triangle triangle)
{
    triangles.push_back(triangle);
}

void Mesh::scale(double factor)
{
    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1 *= factor;
        triangles[t].p2 *= factor;
        triangles[t].p3 *= factor;
    }
}

Mesh Mesh::cube()
{
    return Mesh({
        // front face
        Triangle({0, 0, 0}, {0, 1, 0}, {1, 0, 0}),
        Triangle({1, 0, 0}, {0, 1, 0}, {1, 1, 0}),
        // bottom face
        Triangle({0, 1, 0}, {0, 1, 1}, {1, 1, 0}),
        Triangle({1, 1, 0}, {0, 1, 1}, {1, 1, 1}),
        // back face
        Triangle({0, 0, 1}, {0, 1, 1}, {1, 0, 1}),
        Triangle({1, 0, 1}, {0, 1, 1}, {1, 1, 1}),
        // top face
        Triangle({0, 0, 0}, {0, 0, 1}, {1, 0, 0}),
        Triangle({1, 0, 0}, {0, 0, 1}, {1, 0, 1}),
        // left face
        Triangle({0, 0, 1}, {0, 1, 1}, {0, 0, 0}),
        Triangle({0, 0, 0}, {0, 1, 1}, {0, 1, 0}),
        // right face
        Triangle({1, 0, 0}, {1, 0, 1}, {1, 1, 0}),
        Triangle({1, 1, 0}, {1, 1, 1}, {1, 0, 1})
    });
}