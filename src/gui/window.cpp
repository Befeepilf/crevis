#include "gui/canvas.hpp"
#include "gui/window.hpp"
#include "renderer/renderer.hpp"
#include "renderer/mesh.hpp"
#include "renderer/triangle.hpp"
#include "renderer/vector/vector.hpp"

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>


Window::Window(QWidget* parent) : QMainWindow(parent) {
    showStatus("Building UI...");

    setWindowTitle("Crevis");

    createMenus();

    Canvas* canvas = new Canvas();
    setCentralWidget(canvas);

    Renderer* renderer = new Renderer;

    connect(renderer, &Renderer::renderedFrame, canvas, &Canvas::draw);

    showStatus("Ready");
}

void Window::createMenus() {
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
}

void Window::showStatus(char* msg) {
    statusBar()->showMessage(tr(msg));
}