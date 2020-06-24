#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"

Mesh::Mesh(std::vector<Triangle> triangles) : triangles(triangles)
{

}

void Mesh::addTriangle(Triangle triangle)
{
    triangles.push_back(triangle);
}