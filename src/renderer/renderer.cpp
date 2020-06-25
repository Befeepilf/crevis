#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QImage>

#include <cmath>
#include <iostream>
#include <vector>


Renderer::Renderer(std::vector<Mesh*> meshes) : meshes(meshes)
{
    width = 200;
    height = 200;
    aspectRatio = height / width;
    focalLen = 0.5;
}

double Renderer::getFocalLen()
{
    return focalLen * 200;
}

void Renderer::setSize(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    aspectRatio = (double) height / (double) width;

    render();
}

void Renderer::addMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
    emit addedMesh(mesh);
    render();
}

void Renderer::createCube()
{
    Mesh* cube = Mesh::cube();
    addMesh(cube);
}

void Renderer::setFocalLen(double newFocalLen)
{
    if (newFocalLen != focalLen) emit focalLenChanged(newFocalLen);
    focalLen = newFocalLen / 200;
    render();
}

void Renderer::drawLine(Vec2d p1, Vec2d p2)
{
    int xStart, xEnd;
    if (p1.x() < p2.x())
    {
        xStart = p1.x();
        xEnd = p2.x();
    }
    else
    {
        xStart = p2.x();
        xEnd = p1.x();
    }

    int yStart, yEnd;
    if (p1.y() < p2.y())
    {
        yStart = p1.y();
        yEnd = p2.y();
    }
    else
    {
        yStart = p2.y();
        yEnd = p1.y();
    }

    unsigned int len = 0;
    len += pow(xEnd - xStart, 2);
    len += pow(yEnd - yStart, 2);
    len = sqrt(len);

    unsigned currLen = 0;
    while (currLen < len)
    {
        int pixelX = xStart + currLen * (xEnd - xStart) / len;
        int pixelY = yStart + currLen * (yEnd - yStart) / len;

        if (pixelX < width && pixelX >= 0 && pixelY < height && pixelY >= 0)
        {
            image->setPixelColor(pixelX, pixelY, Qt::red);
        }

        currLen++;
    }
}

Vec2d Renderer::projectVec3d(Vec3d v)
{
    double fovCorrW = focalLen / 0.5;
    double fovCorrH = focalLen / 0.5;

    int x = width/2 * v.x() * fovCorrW * aspectRatio / (v.z() + 1 + focalLen) + width/2;
    int y = height/2 * v.y() * fovCorrH / (v.z() + 1 + focalLen) + height/2;

    return Vec2d(x, y);
}

void Renderer::render()
{
    std::cout << "Rendering image..." << std::endl;

    image = new QImage(width, height, QImage::Format_RGB32);

    for (Mesh* m : meshes)
    {
        std::cout << "Mesh" << std::endl;

        for (Triangle t : m->triangles)
        {
            // 3D projection
            Vec2d p1Proj = projectVec3d(t.p1);
            Vec2d p2Proj = projectVec3d(t.p2);
            Vec2d p3Proj = projectVec3d(t.p3);

            // draw projected triangles
            drawLine(p1Proj, p2Proj);
            drawLine(p2Proj, p3Proj);
            drawLine(p3Proj, p1Proj);
        }
    }

    emit renderedFrame(*image);
}