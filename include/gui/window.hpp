#ifndef WINDOW_H
#define WINDOW_H

#include "renderer/renderer.hpp"

#include <QMainWindow>
#include <QToolBar>

class Window : public QMainWindow
{
    public:
        explicit Window(QWidget* parent = 0);
        
    private:
        void createMenus(void);
        void createToolbar(void);
        void showStatus(char* msg);

        QToolBar* toolbar;
        Renderer* renderer;
};

#endif // WINDOW_H