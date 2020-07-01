#include "file/file.hpp"
#include "file/fileLoader.hpp"
#include "file/parsers/objParser.hpp"
#include "gui/canvas.hpp"
#include "gui/meshesList.hpp"
#include "gui/meshProperties.hpp"
#include "gui/window.hpp"
#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"

#include <QAction>
#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QSlider>
#include <QString>

#include <iostream>


Window::Window(QWidget* parent) : QMainWindow(parent), renderer(new Renderer), fileLoader(new FileLoader)
{
    showStatus("Building UI...");

    setWindowTitle("Crevis");

    createMenus();
    createToolbar();


    Canvas* canvas = new Canvas();
    setCentralWidget(canvas);

    // whenever renderer finished rendering a frame, draw it on the canvas
    connect(renderer, &Renderer::renderedFrame, canvas, &Canvas::draw);
    // whenever size of canvas changes, change size of renderer
    connect(canvas, &Canvas::sizeChanged, renderer, &Renderer::setSize);

    // create a list of all current meshes
    QDockWidget* meshesListWidgetContainer = new QDockWidget(tr("Meshes"), this);
    MeshesList* meshesListWidget = new MeshesList;
    connect(renderer, &Renderer::addedMesh, meshesListWidget, &MeshesList::addMesh);
    meshesListWidgetContainer->setWidget(meshesListWidget);
    addDockWidget(Qt::RightDockWidgetArea, meshesListWidgetContainer);

    // create a widget for setting properties of selectedMesh
    QDockWidget* selectedMeshPropertiesContainer = new QDockWidget(tr("Selected mesh"), this);
    MeshProperties* selectedMeshProperties = new MeshProperties;
    selectedMeshPropertiesContainer->setWidget(selectedMeshProperties);
    selectedMeshPropertiesContainer->widget()->hide();
    addDockWidget(Qt::RightDockWidgetArea, selectedMeshPropertiesContainer);

    // notify selectedMeshProperties whenever a Mesh is selected
    connect(meshesListWidget, &MeshesList::selectedMesh, selectedMeshProperties, &MeshProperties::setMesh);


    showStatus("Ready");
}

void Window::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* importMeshAct = new QAction("Import Mesh");
    connect(importMeshAct, &QAction::triggered, fileLoader, [=] () {
        File* file = fileLoader->openFile({OBJ});
        if (file != nullptr)
        {
            Mesh* mesh = OBJParser::parse(file);
            if (mesh != nullptr) renderer->addMesh(mesh);
        }
    });
    fileMenu->addAction(importMeshAct);
}

void Window::createToolbar()
{
    toolbar = addToolBar(tr("Toolbar"));

    // button for creating a cube
    QAction* createCubeAct = new QAction(tr("Create cube"), this);
    connect(createCubeAct, &QAction::triggered, renderer, &Renderer::createCube);
    toolbar->addAction(createCubeAct);

    // slider for changing focal length
    QSlider* focalLenSlider = new QSlider;
    focalLenSlider->setMinimum(10);
    focalLenSlider->setMaximum(200);
    focalLenSlider->setTickInterval(10);
    focalLenSlider->setValue(renderer->getFocalLen());
    connect(focalLenSlider, &QSlider::valueChanged, renderer, &Renderer::setFocalLen);
    connect(renderer, &Renderer::focalLenChanged, focalLenSlider, &QSlider::setValue);
    toolbar->addWidget(focalLenSlider);

    QLabel* fpsLabel = new QLabel;
    connect(renderer, &Renderer::fps, fpsLabel, qOverload<int>(&QLabel::setNum));
    toolbar->addWidget(fpsLabel);
}

void Window::showStatus(QString msg)
{
    statusBar()->showMessage(msg);
}