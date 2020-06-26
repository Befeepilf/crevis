#include "gui/meshesListItem.hpp"
#include "renderer/mesh.hpp"

MeshesListItem::MeshesListItem(Mesh* mesh) : mesh(mesh)
{
    setText(mesh->name);
}