#ifndef WINDOW_H
#define WINDOW_H

#include "file/fileLoader.hpp"
#include "renderer/renderer.hpp"

#include <QMainWindow>
#include <QString>
#include <QToolBar>

class Window : public QMainWindow
{
    public:
        explicit Window(QWidget* parent = 0);
        
    private:
        void createMenus(void);
        void createToolbar(void);
        void showStatus(QString msg);

        QToolBar* toolbar;
        Renderer* renderer;
        FileLoader* fileLoader;
};

#endif // WINDOW_H