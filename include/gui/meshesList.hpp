#ifndef MESHES_LIST_H
#define MESHES_LST_H

#include "renderer/mesh.hpp"

#include <QListWidget>
#include <QWidget>

class MeshesList : public QListWidget
{
    Q_OBJECT

    public:
        explicit MeshesList(QWidget* parent = 0);

    public slots:
        void addMesh(Mesh* mesh);
};

#endif // MESHES_LIST_H