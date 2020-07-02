#include "gui/rendererSettings.hpp"
#include "renderer/renderer.hpp"

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>


RendererSettings::RendererSettings(Renderer* renderer, QWidget* parent) : QWidget(parent), renderer(renderer)
{
    layout = new QVBoxLayout;

    createFOVSlider();
    createWireframeCheckbox();

    setLayout(layout);
}

void RendererSettings::createFOVSlider()
{
    QFormLayout* focalLenLayout = new QFormLayout;

    QSlider* focalLenSlider = new QSlider;
    focalLenSlider->setMinimum(10);
    focalLenSlider->setMaximum(200);
    focalLenSlider->setTickInterval(10);
    focalLenSlider->setValue(renderer->getFocalLen());
    connect(focalLenSlider, &QSlider::valueChanged, renderer, &Renderer::setFocalLen);
    connect(renderer, &Renderer::focalLenChanged, focalLenSlider, &QSlider::setValue);

    focalLenLayout->addRow(new QLabel("FOV"), focalLenSlider);

    layout->addLayout(focalLenLayout);
}

void RendererSettings::createWireframeCheckbox()
{
    QCheckBox* wireframeCheckbox = new QCheckBox("Show Wireframes");
    connect(wireframeCheckbox, &QCheckBox::stateChanged, renderer, &Renderer::setShowWireframes);
    connect(renderer, &Renderer::showWireframesChanged, wireframeCheckbox, [=] (int state) {
        wireframeCheckbox->setCheckState(static_cast<Qt::CheckState>(state));
    });
    layout->addWidget(wireframeCheckbox);
}