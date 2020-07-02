#ifndef CANVAS_H
#define CANVAS_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>


class Canvas : public QWidget
{
    Q_OBJECT

    public:
        explicit Canvas(QWidget* parent = 0);
        ~Canvas();

        QSize sizeHint(void);
        void resizeEvent(QResizeEvent* event);

    private:
        QGraphicsScene* scene;
        QGraphicsPixmapItem* pixmapItem;

    public slots:
        void draw(QImage img);

    signals:
        void sizeChanged(int width, int height);
};

#endif // CANVAS_H