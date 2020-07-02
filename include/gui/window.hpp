#ifndef WINDOW_H
#define WINDOW_H

#include "file/fileLoader.hpp"
#include "renderer/renderer.hpp"

#include <QAction>
#include <QMainWindow>
#include <QString>
#include <QToolBar>

#include <vector>


class Window : public QMainWindow
{
    public:
        explicit Window(QWidget* parent = 0);
        ~Window();
        
    private:
        void createMenus(void);
        void createToolbar(void);
        void showStatus(QString msg);

        QToolBar* toolbar;
        Renderer* renderer;
        FileLoader* fileLoader;
        std::vector<QAction*> actions;
};

#endif // WINDOW_H