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


    QDockWidget* meshesListWidgetContainer = new QDockWidget(tr("Meshes"), this);
    MeshesList* meshesListWidget = new MeshesList;
    connect(renderer, &Renderer::addedMesh, meshesListWidget, &MeshesList::addMesh);
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
    toolbar = addToolBar(tr("Meshes"));

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
}

void Window::showStatus(char* msg)
{
    statusBar()->showMessage(tr(msg));
}