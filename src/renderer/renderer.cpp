#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QColor>
#include <QImage>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>


Renderer::Renderer(std::vector<Mesh*> meshes) : meshes(meshes)
{
    width = 200;
    height = 200;
    focalLen = 0.5;
    showWireframes = 1;

    cameraPos = new Vec3d(0, 0, -focalLen);
    image = new QImage(width, height, QImage::Format_RGB32);

    setViewportBorderLines();
}

Renderer::~Renderer()
{
    delete cameraPos;

    for (Mesh* m : meshes)
    {
        delete m;
    }

    delete image;
}

void Renderer::setViewportBorderLines()
{
    // boundaries of viewport defined by a point on the line and a vector pointing along the line
    viewportBorderLines = {
        // left vertical line
        {Vec2d(0, 0), Vec2d(0, 1)},
        // right vertical line
        {Vec2d(width - 1, 0), Vec2d(0, -1)},
        // top horizontal line
        {Vec2d(0, 0), Vec2d(-1, 0)},
        // bottom horizontal line
        {Vec2d(0, height - 1), Vec2d(1, 0)}
    };
}

double Renderer::getFocalLen()
{
    return focalLen * 200;
}

void Renderer::setSize(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;

    setViewportBorderLines();

    delete image;
    image = new QImage(width, height, QImage::Format_RGB32);

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

void Renderer::setShowWireframes(int state)
{
    if (state != showWireframes) emit showWireframesChanged(state);
    showWireframes = state;
    render();
}


void Renderer::render()
{
    auto renderStart = std::chrono::high_resolution_clock::now();

    image->fill(0);

    // sort triangles by avgZ to paint farthest triangles first
    std::vector<std::pair<Triangle, double>> trianglesAndFaceDirections = getSortedTrianglesAndFaceDirections();
    
    for (std::pair<Triangle, double> pair : trianglesAndFaceDirections)
    {
        // 3D projection
        Vec2d p1Proj = projectVec3d(pair.first.p1);
        Vec2d p2Proj = projectVec3d(pair.first.p2);
        Vec2d p3Proj = projectVec3d(pair.first.p3);

        // clipping this triangle might result in multiple new triangles
        std::deque<std::vector<Vec2d>> newTriangles = clip2DTriangle(p1Proj, p2Proj, p3Proj);

        for (std::vector<Vec2d> newT : newTriangles)
        {
            unsigned int colorVal = std::max(0, std::min(255, (int) (pair.second * (-255))));
            fillTriangle(newT[0], newT[1], newT[2], QColor (colorVal, colorVal, colorVal));

            if (showWireframes)
            {
                drawLine(newT[0], newT[1], Qt::red);
                drawLine(newT[1], newT[2], Qt::red);
                drawLine(newT[2], newT[0], Qt::red);
            }
        }
    }

    emit renderedFrame(*image);

    auto renderEnd = std::chrono::high_resolution_clock::now();
    auto renderTime = std::chrono::duration_cast<std::chrono::microseconds>(renderEnd - renderStart).count();

    emit fps(1000000 / renderTime);
}

std::vector<std::pair<Triangle, double>> Renderer::getSortedTrianglesAndFaceDirections()
{
    std::vector<std::pair<Triangle, double>> trianglesAndFaceDirections;

    for (Mesh* m : meshes)
    {
        for (Triangle triangle : m->triangles)
        {
            double faceDirection = calcTriangleFaceDirection(triangle);
            
            // filter out triangles not facing the camera
            if (faceDirection < 0)
            {
                if (trianglesAndFaceDirections.size() > 0)
                {
                    // binary insertion sort

                    int l = 0;
                    int r = trianglesAndFaceDirections.size() - 1;
                    unsigned int m;

                    while (l <= r)
                    {
                        m = l + (r - l) / 2;
                        if (trianglesAndFaceDirections[m].first.avgZ < triangle.avgZ)
                        {
                            r = m - 1;
                        }
                        else if (trianglesAndFaceDirections[m].first.avgZ > triangle.avgZ)
                        {
                            l = m + 1;
                        }
                        else
                        {
                            break;
                        }
                    }

                    trianglesAndFaceDirections.insert(
                        trianglesAndFaceDirections.begin() + m,
                        {triangle, faceDirection}
                    );
                }
                else
                {
                    trianglesAndFaceDirections.push_back({triangle, faceDirection});
                }
            }
        }
    }

    return trianglesAndFaceDirections;
}

double Renderer::calcTriangleFaceDirection(Triangle t)
{
    Vec3d normalVec = crossProd(t.p2 - t.p1, t.p3 - t.p1);
    Vec3d viewDir = t.p1 - *cameraPos;
    double faceDirection = normalVec * viewDir; // measurement of how much the triangle faces the camera
    return faceDirection;
}

Vec2d Renderer::projectVec3d(Vec3d v)
{
    double corr = height * focalLen / (v.z() + focalLen);

    int x = v.x() * corr + width/2;
    int y = v.y() * corr + height/2;

    return Vec2d(x, y);
}

std::deque<std::vector<Vec2d>> Renderer::clip2DTriangle(Vec2d p1, Vec2d p2, Vec2d p3)
{
    std::deque<std::vector<Vec2d>> trianglesToClip;
    trianglesToClip.push_back({p1, p2, p3});

    // clip against every border line of viewport
    for (std::pair<Vec2d, Vec2d> line : viewportBorderLines)
    {
        std::deque<std::vector<Vec2d>> newTrianglesToClip;

        while (!trianglesToClip.empty())
        {
            std::vector<Vec2d> currentTriangle = trianglesToClip.front();

            std::vector<Vec2d> pointsBehindLine;
            std::vector<Vec2d> pointsInFrontOfLine;

            for (Vec2d point : currentTriangle)
            {
                // vector from point on line to point of triangle
                Vec2d s = point - line.first;

                // if perp dot product is > 0 than s is clockwise from line and isn't beyond this side of viewport
                if (perpDot(s, line.second) < 0)
                {
                    pointsBehindLine.push_back(point);
                }
                else
                {
                    pointsInFrontOfLine.push_back(point);
                }
            }


            // nothing to clip regarding this line
            if (pointsBehindLine.size() == 0)
            {
                newTrianglesToClip.push_back(currentTriangle);
            }
            // one point lies beyond line -> split into two triangles
            else if (pointsBehindLine.size() == 1)
            {
                // calculate intersection points

                // line from point behind line to point 1 in front of line
                Vec2d s1 = pointsInFrontOfLine[0] - pointsBehindLine[0];
                // line from point behind line to point 2 in front of line
                Vec2d s2 = pointsInFrontOfLine[1] - pointsBehindLine[0];

                // use Cramer's rule to find scaling factors
                double scaleS1 = perpDot(s1, pointsBehindLine[0] - line.first) / perpDot(s1, line.second);
                double scaleS2 = perpDot(s2, pointsBehindLine[0] - line.first) / perpDot(s2, line.second);

                Vec2d intersectionPoint1 = line.first + line.second * scaleS1;
                Vec2d intersectionPoint2 = line.first + line.second * scaleS2;

                // form new triangles
                newTrianglesToClip.push_back({intersectionPoint1, pointsInFrontOfLine[0], pointsInFrontOfLine[1]});
                newTrianglesToClip.push_back({intersectionPoint2, intersectionPoint1, pointsInFrontOfLine[1]});
            }
            else if (pointsBehindLine.size() == 2)
            {   
                // calculate intersection points

                Vec2d s1 = pointsBehindLine[0] - pointsInFrontOfLine[0];
                Vec2d s2 = pointsBehindLine[1] - pointsInFrontOfLine[0];

                double scaleS1 = perpDot(s1, pointsInFrontOfLine[0] - line.first) / perpDot(s1, line.second);
                double scaleS2 = perpDot(s2, pointsInFrontOfLine[0] - line.first) / perpDot(s2, line.second);

                Vec2d intersectionPoint1 = line.first + line.second * scaleS1;
                Vec2d intersectionPoint2 = line.first + line.second * scaleS2;

                // form new triangle
                newTrianglesToClip.push_back({pointsInFrontOfLine[0], intersectionPoint1, intersectionPoint2});
            }

            trianglesToClip.pop_front();
        }

        trianglesToClip = newTrianglesToClip;
    }

    return trianglesToClip;
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
                image->setPixelColor(x, y, color);
            }
       }
   }
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
