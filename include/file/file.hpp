#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QString>

#include <map>


enum FileType {UNKNOWN = -1, OBJ};

extern std::map <QString, FileType> fileTypesByExtension;
extern std::map <FileType, QString> extensionsByFileType;
extern std::map <FileType, QString> descriptionsByFileType;


class File : public QFile
{
    public:
        File(QString fileName);
        FileType fileType;
};

#endif // FILE_H