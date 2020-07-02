#include "gui/canvas.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QResizeEvent>
#include <QSize>
#include <QSizePolicy>
#include <QWidget>


Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    // set size policy
    QSizePolicy sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);


    scene = new QGraphicsScene;

    // create a single QGraphicsPixmapItem which will be modified by the draw() function
    QPixmap initialPixmap;
    pixmapItem = scene->addPixmap(initialPixmap);
    scene->setSceneRect(initialPixmap.rect());

    QGraphicsView* view = new QGraphicsView(scene);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}

Canvas::~Canvas()
{
    delete scene;
}

QSize Canvas::sizeHint()
{
    return QSize(500, 500);
}

void Canvas::resizeEvent(QResizeEvent* event)
{
    emit sizeChanged(width(), height());
}

void Canvas::draw(QImage img)
{
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmapItem->setPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());
}