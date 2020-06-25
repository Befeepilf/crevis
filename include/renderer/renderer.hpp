#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/mesh.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

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
        double focalLength;
        std::vector<Mesh> meshes;
        QImage* image;

        Vec2d projectVec3d(Vec3d v);
        void drawLine(Vec2d p1, Vec2d p2);

    public slots:
        void createCube(void);

    signals:
        void renderedFrame(QImage img);
};

#endif // RENDERER_H