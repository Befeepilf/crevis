#ifndef MESH_H
#define MESH_H

#include "renderer/triangle.hpp"

#include <QObject>

#include <vector>


class Mesh : public QObject
{
    Q_OBJECT

    public:
        Mesh(const char* name = "", std::vector<Triangle> triangles = {});

        const char* name;
        std::vector<Triangle> triangles;

        void addTriangle(Triangle triangle);
        void scale(double factor);
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
        
        static Mesh* cube(void);

    private:
        double angleX;
        double angleY;
        double angleZ;

    signals:
        void changed(void);
};


#endif // MESH_H