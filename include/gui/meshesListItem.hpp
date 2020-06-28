#ifndef MESHES_LIST_ITEM_H
#define MESHES_LIST_ITEM_H

#include "renderer/mesh.hpp"

#include <QListWidgetItem>


class MeshesListItem : public QListWidgetItem
{
    public:
        explicit MeshesListItem(Mesh* mesh);
        Mesh* mesh;
};

#endif // MESHES_LIST_ITEM_H