#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/mesh.hpp"

#include <QImage>
#include <QObject>

#include <vector>


class Renderer : public QObject
{
    Q_OBJECT

    public:
        Renderer(std::vector<Mesh> meshes = {});
        void setWidth(unsigned int width);
        void setHeight(unsigned int height);
        void addMesh(Mesh mesh);
        void render();
    
    private:
        unsigned int width;
        unsigned int height;
        std::vector<Mesh> meshes;

    signals:
        void renderedFrame(QImage img);
};

#endif // RENDERER_H