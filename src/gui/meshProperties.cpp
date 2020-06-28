#include "gui/meshProperties.hpp"
#include "renderer/mesh.hpp"

#include <QHBoxLayout>
#include <QSlider>


MeshProperties::MeshProperties(QWidget* parent) : QWidget(parent), mesh(nullptr)
{
    layout = new QHBoxLayout;
    setLayout(layout);

    // slider for changing X rotation of selected mesh
    rotXSlider = new QSlider;
    rotXSlider->setMinimum(0);
    rotXSlider->setMaximum(360);
    rotXSlider->setTickInterval(1);
    rotXSlider->setValue(0);
    layout->addWidget(rotXSlider);

    // slider for changing Y rotation of selected mesh
    rotYSlider = new QSlider;
    rotYSlider->setMinimum(0);
    rotYSlider->setMaximum(360);
    rotYSlider->setTickInterval(1);
    rotYSlider->setValue(0);
    layout->addWidget(rotYSlider);

    // slider for changing Z rotation of selected mesh
    rotZSlider = new QSlider;
    rotZSlider->setMinimum(0);
    rotZSlider->setMaximum(360);
    rotZSlider->setTickInterval(1);
    rotZSlider->setValue(0);
    layout->addWidget(rotZSlider);
}

void MeshProperties::setMesh(Mesh* newMesh)
{
    if (mesh != nullptr)
    {
        disconnect(rotXSlider, &QSlider::valueChanged, mesh, &Mesh::setXRotation);
        disconnect(rotYSlider, &QSlider::valueChanged, mesh, &Mesh::setYRotation);
        disconnect(rotZSlider, &QSlider::valueChanged, mesh, &Mesh::setZRotation);
    }

    if (newMesh != nullptr)
    {
        rotXSlider->setValue(newMesh->getAngleX());
        rotYSlider->setValue(newMesh->getAngleY());
        rotZSlider->setValue(newMesh->getAngleZ());

        connect(rotXSlider, &QSlider::valueChanged, newMesh, &Mesh::setXRotation);
        connect(rotYSlider, &QSlider::valueChanged, newMesh, &Mesh::setYRotation);
        connect(rotZSlider, &QSlider::valueChanged, newMesh, &Mesh::setZRotation);

        show();
    }
    else
    {
        hide();
    }

    mesh = newMesh;

}