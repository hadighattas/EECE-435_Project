#include "game1graphicsview.h"
#include "game1scene.h"

Game1GraphicsView::Game1GraphicsView(QObject *parent) :
    QGraphicsView(parent)
{
    game1scene *scene1 = new game1scene;

    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene1);
    view->setFixedSize(1280, 641);
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->show();
}
