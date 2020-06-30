#include "math/trig.hpp"
#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"

#include <iostream>

Mesh::Mesh(const char* name, std::vector<Triangle> triangles) : name(name), triangles(triangles)
{
    angleX = 0;
    angleY = 0;
    angleZ = 0;

    translateX = 0;
    translateY = 0;
    translateZ = 0;
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

void Mesh::setXRotation(double deg)
{
    double rad = degToRad(deg);
    double angleChange = rad - angleX;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateX(angleChange);
        triangles[t].p2.rotateX(angleChange);
        triangles[t].p3.rotateX(angleChange);
    }

    angleX = rad;

    emit changed();
}

void Mesh::setYRotation(double deg)
{
    double rad = degToRad(deg);
    double angleChange = rad - angleY;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateY(angleChange);
        triangles[t].p2.rotateY(angleChange);
        triangles[t].p3.rotateY(angleChange);
    }

    angleY = rad;

    emit changed();
}

void Mesh::setZRotation(double deg)
{
    double rad = degToRad(deg);
    double angleChange = rad - angleZ;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.rotateZ(angleChange);
        triangles[t].p2.rotateZ(angleChange);
        triangles[t].p3.rotateZ(angleChange);
    }

    angleZ = rad;

    emit changed();
}


void Mesh::setXTranslation(double newTranslateX)
{
    double translateChange = newTranslateX - translateX;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.translateX(translateChange);
        triangles[t].p2.translateX(translateChange);
        triangles[t].p3.translateX(translateChange);
    }

    translateX = newTranslateX;

    emit changed();
}

void Mesh::setYTranslation(double newTranslateY)
{
    double translateChange = newTranslateY - translateY;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.translateY(translateChange);
        triangles[t].p2.translateY(translateChange);
        triangles[t].p3.translateY(translateChange);
    }

    translateY = newTranslateY;

    emit changed();
}

void Mesh::setZTranslation(double newTranslateZ)
{
    double translateChange = newTranslateZ - translateZ;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].p1.translateZ(translateChange);
        triangles[t].p2.translateZ(translateChange);
        triangles[t].p3.translateZ(translateChange);
    }

    translateZ = newTranslateZ;

    emit changed();
}


double Mesh::getAngleX()
{
    return radToDeg(angleX);
}

double Mesh::getAngleY()
{
    return radToDeg(angleY);
}

double Mesh::getAngleZ()
{
    return radToDeg(angleZ);
}


double Mesh::getTranslationX()
{
    return translateX;
}

double Mesh::getTranslationY()
{
    return translateY;
}

double Mesh::getTranslationZ()
{
    return translateZ;
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
        Triangle({1, 0, 1}, {0, 1, 1}, {0, 0, 1}),
        Triangle({1, 1, 1}, {0, 1, 1}, {1, 0, 1}),
        // top face (anti-clockwise)
        Triangle({1, 0, 0}, {0, 0, 1}, {0, 0, 0}),
        Triangle({1, 0, 1}, {0, 0, 1}, {1, 0, 0}),
        // left face
        Triangle({0, 0, 1}, {0, 1, 1}, {0, 0, 0}),
        Triangle({0, 0, 0}, {0, 1, 1}, {0, 1, 0}),
        // right face (anti-clockwise)
        Triangle({1, 0, 1}, {1, 0, 0}, {1, 1, 0}),
        Triangle({1, 1, 0}, {1, 0, 1}, {1, 1, 1})
    });
}