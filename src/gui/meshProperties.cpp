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
    translateXSlider->setMinimum(-1000);
    translateXSlider->setMaximum(1000);
    translateXSlider->setTickInterval(1);
    translateXSlider->setValue(0);
    translationSlidersLayout->addWidget(translateXSlider);

    // slider for changing Y rotation of selected mesh
    translateYSlider = new QSlider;
    translateYSlider->setMinimum(-1000);
    translateYSlider->setMaximum(1000);
    translateYSlider->setTickInterval(1);
    translateYSlider->setValue(0);
    translationSlidersLayout->addWidget(translateYSlider);

    // slider for changing Z rotation of selected mesh
    translateZSlider = new QSlider;
    translateZSlider->setMinimum(-1000);
    translateZSlider->setMaximum(1000);
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
        while (!connections.empty())
        {
            disconnect(connections.front());
            connections.pop();
        }
    }

    if (newMesh != nullptr)
    {
        // set initial values of rotation sliders
        rotXSlider->setValue(newMesh->getAngleX());
        rotYSlider->setValue(newMesh->getAngleY());
        rotZSlider->setValue(newMesh->getAngleZ());

        // set initial values of translation sliders
        translateXSlider->setValue(newMesh->getTranslationX() * 100);
        translateYSlider->setValue(newMesh->getTranslationY() * 100);
        translateZSlider->setValue(newMesh->getTranslationZ() * 100);

        // connection rotation sliders with newMesh
        connections.push(connect(rotXSlider, &QSlider::valueChanged, newMesh, &Mesh::setXRotation));
        connections.push(connect(rotYSlider, &QSlider::valueChanged, newMesh, &Mesh::setYRotation));
        connections.push(connect(rotZSlider, &QSlider::valueChanged, newMesh, &Mesh::setZRotation));

        // connect translation sliders with newMesh
        connections.push(connect(
            translateXSlider, &QSlider::valueChanged,
            newMesh, [=] (int value) {newMesh->setXTranslation(value / 100.0);}
        ));
        connections.push(connect(
            translateYSlider, &QSlider::valueChanged,
            newMesh, [=] (int value) {newMesh->setYTranslation(value / 100.0);}
        ));
        connections.push(connect(
            translateZSlider, &QSlider::valueChanged,
            newMesh, [=] (int value) {newMesh->setZTranslation(value / 100.0);}
        ));

        show();
    }
    else
    {
        hide();
    }

    mesh = newMesh;

}