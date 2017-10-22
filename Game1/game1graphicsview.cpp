#include "game1graphicsview.h"
#include "game1scene.h"


Game1GraphicsView::Game1GraphicsView(QWidget *parent) : QGraphicsView(parent)
{


    setFixedSize(1280,661);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1Scene *scene1=new Game1Scene;
    setScene(scene1);
    show();
}
