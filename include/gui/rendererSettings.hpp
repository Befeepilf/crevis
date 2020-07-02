#ifndef RENDERER_SETTINGS_H
#define RENDERER_SETTINGS_H


#include "renderer/renderer.hpp"

#include <QVBoxLayout>
#include <QWidget>


class RendererSettings : public QWidget
{
    public:
        explicit RendererSettings(Renderer* renderer, QWidget* parent = 0);
    
    private:
        Renderer* renderer;
        QVBoxLayout* layout;

        void createFOVSlider();
        void createWireframeCheckbox();
};


#endif // RENDERER_SETTINGS_H