#ifndef MESH_H
#define MESH_H

#include "renderer/triangle.hpp"

#include <QObject>
#include <QString>

#include <vector>


class Mesh : public QObject
{
    Q_OBJECT

    public:
        Mesh(QString name, std::vector<Triangle> triangles = {});

        QString name;
        std::vector<Triangle> triangles;

        void addTriangle(Triangle triangle);
        void scale(double factor);

        double getAngleX(void); // returns x rotation in degrees
        double getAngleY(void); // returns y rotation in degrees
        double getAngleZ(void); // returns z rotation in degrees
        
        double getTranslationX(void);
        double getTranslationY(void);
        double getTranslationZ(void);

        static Mesh* cube(void);

    private:
        void calcCenter(void);

        Vec3d* center;

        double angleX;
        double angleY;
        double angleZ;

        double translateX;
        double translateY;
        double translateZ;

    signals:
        void changed(void);

    public slots:
        void setXRotation(double deg);
        void setYRotation(double deg);
        void setZRotation(double deg);

        void setXTranslation(double newTranslateX);
        void setYTranslation(double newTranslateY);
        void setZTranslation(double newTranslateZ);
};


#endif // MESH_H