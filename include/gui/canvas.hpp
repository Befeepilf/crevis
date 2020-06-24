#ifndef CANVAS_H
#define CANVAS_H

#include <QImage>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QSize>
#include <QWidget>


class Canvas : public QWidget
{
    Q_OBJECT

    public:
        explicit Canvas(QWidget* parent = 0);
        QSize sizeHint(void);

    private:
        QGraphicsScene* scene;
        QGraphicsPixmapItem* pixmapItem;

    public slots:
        void draw(QImage img);
};

#endif // CANVAS_H