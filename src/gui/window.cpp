#include "file/file.hpp"
#include "file/fileLoader.hpp"
#include "file/parsers/objParser.hpp"
#include "gui/canvas.hpp"
#include "gui/meshesList.hpp"
#include "gui/meshProperties.hpp"
#include "gui/rendererSettings.hpp"
#include "gui/window.hpp"
#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"

#include <QAction>
#include <QDockWidget>
#include <QFormLayout>
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


    // dock widget for renderer settings
    QDockWidget* rendererSettingsContainer = new QDockWidget(tr("Renderer settings"), this);
    RendererSettings* rendererSettings = new RendererSettings(renderer);
    rendererSettingsContainer->setWidget(rendererSettings);
    addDockWidget(Qt::LeftDockWidgetArea, rendererSettingsContainer);

    showStatus("Ready");
}

Window::~Window()
{
    delete renderer;
    delete fileLoader;
    for (QAction* a : actions)
    {
        delete a;
    }
}

void Window::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* importMeshAct = new QAction("Import Mesh");

    connect(importMeshAct, &QAction::triggered, fileLoader, [=] () {
        File* file = fileLoader->openFile({OBJ});
        if (file != nullptr)
        {
            showStatus("Importing mesh...");
            Mesh* mesh = OBJParser::parse(file);
            delete file;
            if (mesh != nullptr) renderer->addMesh(mesh);
            showStatus("Ready");
        }
    });

    fileMenu->addAction(importMeshAct);

    actions.push_back(importMeshAct);
}

void Window::createToolbar()
{
    toolbar = addToolBar(tr("Toolbar"));


    // button for creating a cube
    QAction* createCubeAct = new QAction(tr("Create cube"), this);
    connect(createCubeAct, &QAction::triggered, renderer, &Renderer::createCube);
    toolbar->addAction(createCubeAct);


    QLabel* fpsLabel = new QLabel;
    connect(renderer, &Renderer::fps, fpsLabel, [=] (unsigned int fps) {
        fpsLabel->setText(QString("FPS: %1").arg(fps));
    });
    toolbar->addWidget(fpsLabel);
}

void Window::showStatus(QString msg)
{
    statusBar()->showMessage(msg);
}