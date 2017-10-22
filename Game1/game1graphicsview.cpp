/**
 * \file graphics1view.cpp
 * \brief Setting up the GraphicsViews
*/
#include "game1graphicsview.h"
#include "game1scene.h"


Game1GraphicsView::Game1GraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void Game1GraphicsView::setDifficulty(int diff) {
    this->difficulty = diff;
    setFixedSize(1280,661);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game1Scene *scene1=new Game1Scene;
    scene1->setDifficulty(difficulty);
    setScene(scene1);
    show();
}
