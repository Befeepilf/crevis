#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QColor>
#include <QImage>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>


Renderer::Renderer(std::vector<Mesh*> meshes) : meshes(meshes)
{
    width = 200;
    height = 200;
    aspectRatio = height / width;
    focalLen = 0.5;

    cameraPos = new Vec3d(0, 0, -focalLen);
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
    cameraPos->components[2] = -focalLen;
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

        if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < height)
        {
            image->setPixelColor(pixelX, pixelY, color);
        }

        currLen++;
    }
}

void Renderer::fillTriangle(Vec2d p1, Vec2d p2, Vec2d p3, QColor color)
{
    // calculate two side lengths spanning a plane
    Vec2d s1 = (p2 - p1);
    Vec2d s2 = (p3 - p1);

    // find bounding box of triangle
    double xMin = std::min(p1.x(), std::min(p2.x(), p3.x()));
    double xMax = std::max(p1.x(), std::max(p2.x(), p3.x()));
    double yMin = std::min(p1.y(), std::min(p2.y(), p3.y()));
    double yMax = std::max(p1.y(), std::max(p2.y(), p3.y()));
    
    /*
        Using Barycentric coordinates to determine whether
        a point liesinside the triangle:

        P(a, b) = p1 + a * s1 + b * s2
        where a, b >= 0 and (a + b) <= 1
        describes all points inside the triangle

        equation to solve:
            P - p1 = a * s1 + b * s2

        -> use Cramer's rule
    */

   for (unsigned int x = xMin; x <= xMax; x++)
   {
       for (unsigned int y = yMin; y <= yMax; y++)
       {
            Vec2d P (x - p1.x(), y - p1.y());

            /*
                Cramer's rule
                the perp dot product of two 2d vectors is equivalent
                to the determinant of a 2x2 matrix where its columns
                are these two vectors
            */
            double fac = 1 / perpDot(s1, s2);
            double a = perpDot(P, s2) * fac;
            double b = perpDot(s1, P) * fac;

            // if point is inside triangle, draw it
            if (a >= 0 && b >= 0 && (a + b) <= 1)
            {
                if (x >= 0 && x < width && y >= 0 && y < height)
                {
                    image->setPixelColor(x, y, color);
                }
            }
       }
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

    std::vector<Triangle> triangles;

    // collect all triangles in a single vector sorted by avgZ
    // to paint farthest triangles first
    for (Mesh* m : meshes)
    {
        for (Triangle t : m->triangles)
        {
            // Vec3d normalVec = crossProd(t.p2 - t.p1, t.p3 - t.p1);
            // Vec3d viewDir = t.p1 - *cameraPos;

            // std::cout << "l1: " << (t.p2 - t.p1).x() << ", " << (t.p2 - t.p1).y() << ", " << (t.p2 - t.p1).z() << std::endl;
            // std::cout << "l2: " << (t.p3 - t.p1).x() << ", " << (t.p3 - t.p1).y() << ", " << (t.p3 - t.p1).z() << std::endl;
            // std::cout << "normal: " << normalVec.x() << ", " << normalVec.y() << ", " << normalVec.z() << std::endl;
            // std::cout << "view: " << viewDir.x() << ", " << viewDir.y() << ", " << viewDir.z() << std::endl;
            // std::cout << "-> " << normalVec * viewDir << std::endl;

            // filter out triangles not facing the camera
            if (/*normalVec * viewDir < 0 || */1)
            {
                if (triangles.size() > 0)
                {
                    int l = 0;
                    int r = triangles.size() - 1;
                    unsigned int m;

                    while (l <= r)
                    {
                        m = l + (r - l) / 2;
                        if (triangles[m].avgZ < t.avgZ)
                        {
                            r = m - 1;
                        }
                        else if (triangles[m].avgZ > t.avgZ)
                        {
                            l = m + 1;
                        }
                        else
                        {
                            break;
                        }
                    }

                    triangles.insert(triangles.begin() + m, t);
                }
                else
                {
                    triangles.push_back(t);
                }
            }
        }
    }

    for (Triangle t : triangles)
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

    emit renderedFrame(*image);
}