#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"

#include <QImage>

#include <vector>


Renderer::Renderer(std::vector<Mesh> meshes) : meshes(meshes)
{

}

void Renderer::addMesh(Mesh mesh)
{
    meshes.push_back(mesh);
}

void Renderer::render()
{
    QImage image (200, 200, QImage::Format_RGB32);

    for (Mesh m : meshes)
    {
        for (Triangle t : m.triangles)
        {
            // TODO
        }
    }

    emit renderedFrame(image);
}