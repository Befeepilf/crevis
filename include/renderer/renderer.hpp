#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/mesh.hpp"
#include "renderer/vector/vec2d.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QColor>
#include <QImage>
#include <QObject>

#include <vector>


class Renderer : public QObject
{
    Q_OBJECT

    public:
        Renderer(std::vector<Mesh*> meshes = {});
        double getFocalLen();
        void setWidth(unsigned int width);
        void setHeight(unsigned int height);
        void addMesh(Mesh* mesh);
    
    private:
        unsigned int width;
        unsigned int height;
        double focalLen;
        std::vector<Mesh*> meshes;
        Mesh* selectedMesh;
        QImage* image;
        Vec3d* cameraPos;

        Vec2d projectVec3d(Vec3d v);
        void drawLine(Vec2d p1, Vec2d p2, QColor color);
        void fillTriangle(Vec2d p1, Vec2d p2, Vec2d p3, QColor color);

    public slots:
        void setSize(int newWidth, int newHeight);
        void createCube(void);
        void setFocalLen(double newFocalLen);

        void render();

    signals:
        void renderedFrame(QImage img);
        void fps(unsigned int fps);
        void focalLenChanged(double focalLen);
        void addedMesh(Mesh* mesh);
};

#endif // RENDERER_H