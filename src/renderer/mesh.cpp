#include "math/trig.hpp"
#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"

#include <QString>

#include <iostream>


Mesh::Mesh(QString name, std::vector<Triangle> triangles) : name(name), triangles(triangles)
{
    angleX = 0;
    angleY = 0;
    angleZ = 0;

    translateX = 0;
    translateY = 0;
    translateZ = 0;

    center = new Vec3d(0, 0, 0);
    calcCenter();

    setZTranslation(10);
}

Mesh::~Mesh()
{
    delete center;
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
        triangles[t].scale(factor);
    }

    emit changed();
}


void Mesh::setXRotation(double deg)
{
    double rad = degToRad(deg);
    double angleChange = rad - angleX;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].translate((*center) * -1);
        triangles[t].rotateX(angleChange);
        triangles[t].translate(*center);
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
        triangles[t].translate((*center) * -1);
        triangles[t].rotateY(angleChange);
        triangles[t].translate(*center);
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
        triangles[t].translate((*center) * -1);
        triangles[t].rotateZ(angleChange);
        triangles[t].translate(*center);
    }

    angleZ = rad;

    emit changed();
}


void Mesh::setXTranslation(double newTranslateX)
{
    double translateChange = newTranslateX - translateX;

    for (unsigned int t = 0; t < triangles.size(); t++)
    {
        triangles[t].translateX(translateChange);
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
        triangles[t].translateY(translateChange);
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
        triangles[t].translateZ(translateChange);
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