#ifndef MESH_PROPERTIES_H
#define MESH_PROPERTIES_H


#include "renderer/mesh.hpp"

#include <QHBoxLayout>
#include <QSlider>
#include <QWidget>


class MeshProperties : public QWidget
{
    Q_OBJECT

    public:
        explicit MeshProperties(QWidget* parent = 0);

    private:
        QHBoxLayout* layout;
        QSlider* rotXSlider;
        QSlider* rotYSlider;
        QSlider* rotZSlider;

        Mesh* mesh;

    public slots:
        void setMesh(Mesh* newMesh);
};

#endif // MESH_PROPERTIES_H