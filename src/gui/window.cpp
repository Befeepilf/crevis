#include "gui/canvas.hpp"
#include "gui/meshesList.hpp"
#include "gui/window.hpp"
#include "renderer/renderer.hpp"

#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QSlider>


Window::Window(QWidget* parent) : QMainWindow(parent), renderer(new Renderer)
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
    connect(meshesListWidget, &MeshesList::selectedMesh, renderer, &Renderer::setSelectedMesh);
    meshesListWidgetContainer->setWidget(meshesListWidget);
    addDockWidget(Qt::RightDockWidgetArea, meshesListWidgetContainer);

    showStatus("Ready");
}

void Window::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
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


    toolbar->addSeparator();


    // slider for changing X rotation of selected mesh
    QSlider* rotXSlider = new QSlider;
    rotXSlider->setMinimum(0);
    rotXSlider->setMaximum(314);
    rotXSlider->setTickInterval(1);
    rotXSlider->setValue(0);
    connect(rotXSlider, &QSlider::valueChanged, renderer, &Renderer::setXRotOfSelectedMesh);
    toolbar->addWidget(rotXSlider);

    // slider for changing Y rotation of selected mesh
    QSlider* rotYSlider = new QSlider;
    rotYSlider->setMinimum(0);
    rotYSlider->setMaximum(314);
    rotYSlider->setTickInterval(1);
    rotYSlider->setValue(0);
    connect(rotYSlider, &QSlider::valueChanged, renderer, &Renderer::setYRotOfSelectedMesh);
    toolbar->addWidget(rotYSlider);

    // slider for changing Z rotation of selected mesh
    QSlider* rotZSlider = new QSlider;
    rotZSlider->setMinimum(0);
    rotZSlider->setMaximum(314);
    rotZSlider->setTickInterval(1);
    rotZSlider->setValue(0);
    connect(rotZSlider, &QSlider::valueChanged, renderer, &Renderer::setZRotOfSelectedMesh);
    toolbar->addWidget(rotZSlider);
}

void Window::showStatus(char* msg)
{
    statusBar()->showMessage(tr(msg));
}