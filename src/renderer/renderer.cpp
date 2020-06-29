#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QColor>
#include <QImage>

#include <cmath>
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
    connect(mesh, &Mesh::changed, this, &Renderer::render);
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

void Renderer::drawLine(Vec2d p1, Vec2d p2, QColor color)
{
    double len = 0;
    len += pow(p1.x() - p2.x(), 2);
    len += pow(p1.y() - p2.y(), 2);
    len = sqrt(len);

    unsigned int currLen = 0;
    while (currLen < len)
    {
        const int pixelX = round(p1.x() + currLen * (p2.x() - p1.x()) / len);
        const int pixelY = round(p1.y() + currLen * (p2.y() - p1.y()) / len);

        if (pixelX < width && pixelX >= 0 && pixelY < height && pixelY >= 0)
        {
            image->setPixelColor(pixelX, pixelY, color);
        }

        currLen++;
    }
}

void Renderer::fillTriangle(Vec2d p1, Vec2d p2, Vec2d p3, QColor color)
{
    // calculate side lengths
    // define p1 -> p2 as base
    Vec2d s1 = (p3 - p1);
    Vec2d s2 = (p3 - p2);
    
    double bLen = (p2 - p1).length();
    double s1Len = s1.length();
    double s2Len = s2.length();

    Vec2d s1Norm = s1 / s1Len;
    Vec2d s2Norm = s2 / s2Len;

    // calculate height of triangle
    double height = sqrt(pow(s2Len, 2) - (pow(bLen, 2) - pow(s1Len, 2) + pow(s2Len, 2)) / (2 * bLen));

    double currHeight = 0;
    while (currHeight < height)
    {
        Vec2d lineStart = p1 + s1Norm * s1Len / height * currHeight;
        Vec2d lineEnd = p2 + s2Norm * s2Len / height * currHeight;
        drawLine(lineStart, lineEnd, color);
        
        // go half steps to make sure not pixel is left out
        currHeight += 0.5;
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
    image = new QImage(width, height, QImage::Format_RGB32);

    for (Mesh* m : meshes)
    {
        for (Triangle t : m->triangles)
        {
            // 3D projection
            Vec2d p1Proj = projectVec3d(t.p1);
            Vec2d p2Proj = projectVec3d(t.p2);
            Vec2d p3Proj = projectVec3d(t.p3);

            // fill projected triangle
            fillTriangle(p1Proj, p2Proj, p3Proj, Qt::gray);

            // draw outlines of projected triangle
            drawLine(p1Proj, p2Proj, Qt::red);
            drawLine(p2Proj, p3Proj, Qt::red);
            drawLine(p3Proj, p1Proj, Qt::red);
        }
    }

    emit renderedFrame(*image);
}