#ifndef FILE_LOADER_H
#define FILE_LOADER_H


#include "file/file.hpp"

#include <QString>
#include <QWidget>

#include <vector>

class FileLoader : public QWidget
{
    Q_OBJECT

    public:
        explicit FileLoader(QWidget* parent = 0);

    private:
        QString getFilterString(std::vector<FileType> fileTypes);
    
    public slots:
        File* openFile(std::vector<FileType> allowedFileTypes);
};


#endif // FILE_LOADER_H