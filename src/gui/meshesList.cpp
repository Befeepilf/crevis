#include "gui/meshesList.hpp"

#include <QListWidget>
#include <QWidget>

MeshesList::MeshesList(QWidget* parent) : QListWidget(parent)
{

}

void MeshesList::addMesh(Mesh* mesh)
{
    addItem(mesh->name);
}