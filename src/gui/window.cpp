#include "gui/canvas.hpp"
#include "gui/window.hpp"
#include "renderer/renderer.hpp"

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>


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

    showStatus("Ready");
}

void Window::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
}

void Window::createToolbar()
{
    toolbar = addToolBar(tr("Meshes"));

    QAction* createCubeAct = new QAction(tr("Create cube"), this);
    connect(createCubeAct, &QAction::triggered, renderer, &Renderer::createCube);
    toolbar->addAction(createCubeAct);
}

void Window::showStatus(char* msg)
{
    statusBar()->showMessage(tr(msg));
}