#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class Window : public QMainWindow
{
    public:
        explicit Window(QWidget* parent = 0);
    private:
        void createMenus(void);
        void showStatus(char* msg);
};

#endif // WINDOW_H