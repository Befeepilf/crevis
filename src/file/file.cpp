#include "file/file.hpp"

#include <QFile>
#include <QFileInfo>
#include <QString>

#include <map>


std::map <QString, FileType> fileTypesByExtension = {
    {"obj", OBJ},
};

std::map <FileType, QString> extensionsByFileType = {
    {OBJ, "obj"}
};

std::map <FileType, QString> descriptionsByFileType = {
    {OBJ, "Wavefront OBJ File"}
};


File::File(QString fileName) : QFile(fileName)
{
    QFileInfo fileInfo (*this);
    fileType = fileTypesByExtension.at(fileInfo.completeSuffix());
}