#ifndef MESH_PROPERTIES_H
#define MESH_PROPERTIES_H


#include "renderer/mesh.hpp"

#include <QVBoxLayout>
#include <QSlider>
#include <QWidget>


class MeshProperties : public QWidget
{
    Q_OBJECT

    public:
        explicit MeshProperties(QWidget* parent = 0);

    private:
        void createRotationSliders(void);
        void createTranslationSliders(void);

        QVBoxLayout* layout;

        QSlider* rotXSlider;
        QSlider* rotYSlider;
        QSlider* rotZSlider;

        QSlider* translateXSlider;
        QSlider* translateYSlider;
        QSlider* translateZSlider;

        Mesh* mesh;

    public slots:
        void setMesh(Mesh* newMesh);
};

#endif // MESH_PROPERTIES_H