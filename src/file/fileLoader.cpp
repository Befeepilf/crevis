#include "file/file.hpp"
#include "file/fileLoader.hpp"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <QWidget>

#include <iostream>

FileLoader::FileLoader(QWidget* parent) : QWidget(parent)
{
}

File* FileLoader::openFile(std::vector<FileType> allowedFileTypes)
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Import Mesh"), // caption
        "", // initial directory
        getFilterString(allowedFileTypes)
    );

    if (fileName.isEmpty()) return 0;

    File* file = new File(fileName);

    // check whether file is readable
    if (!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Unable to open file"), file->errorString());
        delete file;
        return 0;
    }

    file->close();

    return file;
}

QString FileLoader::getFilterString(std::vector<FileType> fileTypes)
{
    QString filterString = "";
    
    for (unsigned int i = 0; i < fileTypes.size(); i++)
    {
        if (i > 0) filterString += ";;";
        filterString += descriptionsByFileType.at(fileTypes[i]);
        filterString += "(*.";
        filterString += extensionsByFileType.at(fileTypes[i]);
        filterString += ")";
    }

    return filterString;
}