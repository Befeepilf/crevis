#include "file/file.hpp"
#include "file/parsers/objParser.hpp"
#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"
#include "renderer/vector/vec3d.hpp"

#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <iostream>
#include <vector>


Mesh* OBJParser::parse(File* file)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0, "Unable to open file", file->errorString());
        return 0;
    }


    QString name = "";
    std::vector<Vec3d> geometricVertices;
    std::vector<Triangle> triangles;

    QTextStream in(file);
    while (!in.atEnd())
    {

        QString line = in.readLine();
        if (line.startsWith('#')) continue;
        
        QStringList lineSplit = line.split(' ');
        QString lineType = lineSplit.at(0);

        // object name
        if (lineType == "o")
        {
            name = lineSplit.at(1);
        }
        // geometric vertex (x, y, z [, w])
        // w is optional and defaults to 1.0
        else if (lineType == "v")
        {
            geometricVertices.push_back(Vec3d(
                lineSplit.at(1).toDouble(),
                lineSplit.at(2).toDouble(),
                lineSplit.at(3).toDouble()
            ));
        }
        // texture coordinate (u [, v] [, w])
        // values between 0 and 1
        // v and w are optional and default to 0
        else if (lineType == "vt")
        {
            continue;
        }
        // vertext normal (x, y, z)
        else if (lineType == "vn")
        {
            continue;
        }
        // parameter space vertex (u [, v] [, w])
        // v and w are optional
        else if (lineType == "vp")
        {
            continue;
        }
        // polygonal face element
        // formats:
        //      vertex_index ...
        //      vertex_index/texture_index ...
        //      vertex_index//normal_index ...
        //      vertex_index/texture_index/normal_index ...
        // each index starts at 1
        else if (lineType == "f")
        {
            // triangle
            if (lineSplit.size() == 4)
            {
                triangles.push_back(Triangle(
                    geometricVertices[lineSplit.at(3).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(2).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(1).split('/').at(0).toUInt() - 1]
                ));
            }
            // rectangle -> split into two triangles
            else if (lineSplit.size() == 5)
            {
                triangles.push_back(Triangle(
                    geometricVertices[lineSplit.at(3).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(2).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(1).split('/').at(0).toUInt() - 1]
                ));

                triangles.push_back(Triangle(
                    geometricVertices[lineSplit.at(3).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(1).split('/').at(0).toUInt() - 1],
                    geometricVertices[lineSplit.at(4).split('/').at(0).toUInt() - 1]
                ));
            }
        }
        // line element
        else if (lineType == "l")
        {
            continue;
        }
        else continue;
    }

    return new Mesh(name, triangles);
}