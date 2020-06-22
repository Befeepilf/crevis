#include "gui/window.hpp"

Window::Window(QWidget* parent) : QWidget(parent) {
    setMinimumWidth(200);
    setMinimumHeight(100);
    setBaseSize(200, 100);
}