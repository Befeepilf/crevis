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

        double getAngleX(void); // returns x rotation in degrees
        double getAngleY(void); // returns y rotation in degrees
        double getAngleZ(void); // returns z rotation in degrees
        
        static Mesh* cube(void);

    private:
        double angleX;
        double angleY;
        double angleZ;

    signals:
        void changed(void);

    public slots:
        void setXRotation(double deg);
        void setYRotation(double deg);
        void setZRotation(double deg);
};


#endif // MESH_H