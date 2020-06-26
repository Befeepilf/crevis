#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"

#include <iostream>

Mesh::Mesh(const char* name, std::vector<Triangle> triangles) : name(name), triangles(triangles)
{
    angleX = 0;
    angleY = 0;
    angleZ = 0;
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

    emit changed();
}

void Mesh::rotateX(double angle)
{
    double angleChange = angle - angleX;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateX(angleChange);
        triangles[t].p2.rotateX(angleChange);
        triangles[t].p3.rotateX(angleChange);
    }

    angleX = angle;

    emit changed();
}

void Mesh::rotateY(double angle)
{
    double angleChange = angle - angleY;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateY(angleChange);
        triangles[t].p2.rotateY(angleChange);
        triangles[t].p3.rotateY(angleChange);
    }

    angleY = angle;

    emit changed();
}

void Mesh::rotateZ(double angle)
{
    double angleChange = angle - angleZ;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateZ(angleChange);
        triangles[t].p2.rotateZ(angleChange);
        triangles[t].p3.rotateZ(angleChange);
    }

    angleZ = angle;

    emit changed();
}


Mesh* Mesh::cube()
{
    return new Mesh("Cube", {
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