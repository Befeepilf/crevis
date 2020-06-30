#include "gui/window.hpp"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app (argc, argv);

    Window window;
    window.setWindowState(Qt::WindowMaximized);
    window.show();

    return app.exec();
}