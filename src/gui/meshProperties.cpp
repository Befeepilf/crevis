#include "gui/meshProperties.hpp"
#include "renderer/mesh.hpp"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QSlider>
#include <QVBoxLayout>


MeshProperties::MeshProperties(QWidget* parent) : QWidget(parent), mesh(nullptr)
{
    layout = new QVBoxLayout;
    setLayout(layout);

    createRotationSliders();
    createTranslationSliders();
}

void MeshProperties::createRotationSliders()
{
    QGroupBox* rotationSlidersGroup = new QGroupBox(tr("Rotation"));
    QHBoxLayout* rotationSlidersLayout = new QHBoxLayout;

    // slider for changing X rotation of selected mesh
    rotXSlider = new QSlider;
    rotXSlider->setMinimum(0);
    rotXSlider->setMaximum(360);
    rotXSlider->setTickInterval(1);
    rotXSlider->setValue(0);
    rotationSlidersLayout->addWidget(rotXSlider);

    // slider for changing Y rotation of selected mesh
    rotYSlider = new QSlider;
    rotYSlider->setMinimum(0);
    rotYSlider->setMaximum(360);
    rotYSlider->setTickInterval(1);
    rotYSlider->setValue(0);
    rotationSlidersLayout->addWidget(rotYSlider);

    // slider for changing Z rotation of selected mesh
    rotZSlider = new QSlider;
    rotZSlider->setMinimum(0);
    rotZSlider->setMaximum(360);
    rotZSlider->setTickInterval(1);
    rotZSlider->setValue(0);
    rotationSlidersLayout->addWidget(rotZSlider);

    rotationSlidersGroup->setLayout(rotationSlidersLayout);
    layout->addWidget(rotationSlidersGroup);
}

void MeshProperties::createTranslationSliders()
{
    QGroupBox* translationSlidersGroup = new QGroupBox(tr("Translation"));
    QHBoxLayout* translationSlidersLayout = new QHBoxLayout;

    // slider for changing X rotation of selected mesh
    translateXSlider = new QSlider;
    translateXSlider->setMinimum(-100);
    translateXSlider->setMaximum(100);
    translateXSlider->setTickInterval(1);
    translateXSlider->setValue(0);
    translationSlidersLayout->addWidget(translateXSlider);

    // slider for changing Y rotation of selected mesh
    translateYSlider = new QSlider;
    translateYSlider->setMinimum(-100);
    translateYSlider->setMaximum(100);
    translateYSlider->setTickInterval(1);
    translateYSlider->setValue(0);
    translationSlidersLayout->addWidget(translateYSlider);

    // slider for changing Z rotation of selected mesh
    translateZSlider = new QSlider;
    translateZSlider->setMinimum(-100);
    translateZSlider->setMaximum(100);
    translateZSlider->setTickInterval(1);
    translateZSlider->setValue(0);
    translationSlidersLayout->addWidget(translateZSlider);

    translationSlidersGroup->setLayout(translationSlidersLayout);
    layout->addWidget(translationSlidersGroup);
}

void MeshProperties::setMesh(Mesh* newMesh)
{
    if (mesh != nullptr)
    {
        disconnect(rotXSlider, &QSlider::valueChanged, mesh, &Mesh::setXRotation);
        disconnect(rotYSlider, &QSlider::valueChanged, mesh, &Mesh::setYRotation);
        disconnect(rotZSlider, &QSlider::valueChanged, mesh, &Mesh::setZRotation);

        disconnect(translateXSlider, &QSlider::valueChanged, mesh, &Mesh::setXTranslation);
        disconnect(translateYSlider, &QSlider::valueChanged, mesh, &Mesh::setYTranslation);
        disconnect(translateZSlider, &QSlider::valueChanged, mesh, &Mesh::setZTranslation);
    }

    if (newMesh != nullptr)
    {
        rotXSlider->setValue(newMesh->getAngleX());
        rotYSlider->setValue(newMesh->getAngleY());
        rotZSlider->setValue(newMesh->getAngleZ());

        translateXSlider->setValue(newMesh->getTranslationX() * 100);
        translateYSlider->setValue(newMesh->getTranslationY() * 100);
        translateZSlider->setValue(newMesh->getTranslationZ() * 100);

        connect(rotXSlider, &QSlider::valueChanged, newMesh, &Mesh::setXRotation);
        connect(rotYSlider, &QSlider::valueChanged, newMesh, &Mesh::setYRotation);
        connect(rotZSlider, &QSlider::valueChanged, newMesh, &Mesh::setZRotation);

        connect(translateXSlider, &QSlider::valueChanged, newMesh, [=] (int value) {newMesh->setXTranslation(value / 100.0);});
        connect(translateYSlider, &QSlider::valueChanged, newMesh, [=] (int value) {newMesh->setYTranslation(value / 100.0);});
        connect(translateZSlider, &QSlider::valueChanged, newMesh, [=] (int value) {newMesh->setZTranslation(value / 100.0);});

        show();
    }
    else
    {
        hide();
    }

    mesh = newMesh;

}