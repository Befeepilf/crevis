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

    center = new Vec3d(0, 0, 0);
    calcCenter();
}

void Mesh::calcCenter()
{
    Vec3d newCenter (0, 0, 0);

    for (Triangle t : triangles)
    {
        newCenter += t.p1;
        newCenter += t.p2;
        newCenter += t.p3;
    }

    newCenter /= triangles.size() * 3;

    center->components[0] = newCenter.x();
    center->components[1] = newCenter.y();
    center->components[2] = newCenter.z();
}

void Mesh::addTriangle(Triangle triangle)
{
    triangles.push_back(triangle);
    calcCenter();
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
        triangles[t].p1 -= *center;
        triangles[t].p2 -= *center;
        triangles[t].p3 -= *center;

        triangles[t].p1.rotateX(angleChange);
        triangles[t].p2.rotateX(angleChange);
        triangles[t].p3.rotateX(angleChange);

        triangles[t].p1 += *center;
        triangles[t].p2 += *center;
        triangles[t].p3 += *center;
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
        triangles[t].p1 -= *center;
        triangles[t].p2 -= *center;
        triangles[t].p3 -= *center;

        triangles[t].p1.rotateY(angleChange);
        triangles[t].p2.rotateY(angleChange);
        triangles[t].p3.rotateY(angleChange);

        triangles[t].p1 += *center;
        triangles[t].p2 += *center;
        triangles[t].p3 += *center;
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
        triangles[t].p1 -= *center;
        triangles[t].p2 -= *center;
        triangles[t].p3 -= *center;

        triangles[t].p1.rotateZ(angleChange);
        triangles[t].p2.rotateZ(angleChange);
        triangles[t].p3.rotateZ(angleChange);

        triangles[t].p1 += *center;
        triangles[t].p2 += *center;
        triangles[t].p3 += *center;
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

    calcCenter();

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

    calcCenter();

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

    calcCenter();

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
        Triangle({1, 1, 1}, {1, 0, 1}, {1, 1, 0})
    });
}