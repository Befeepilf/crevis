#include "gui/meshesList.hpp"
#include "gui/meshesListItem.hpp"

#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>

MeshesList::MeshesList(QWidget* parent) : QListWidget(parent)
{
    connect(this, &MeshesList::currentItemChanged, this, &MeshesList::selectMesh);
}

void MeshesList::addMesh(Mesh* mesh)
{
    MeshesListItem* item = new MeshesListItem(mesh);
    addItem(item);
}

void MeshesList::selectMesh(QListWidgetItem* listWidgetItem)
{
    // we only add MeshesListItem to the QListWidget so we know that QListWidgetItem* is actually MeshesListItem*
    MeshesListItem* meshesListItem = static_cast<MeshesListItem*>(listWidgetItem);
    emit selectedMesh(meshesListItem->mesh);
}