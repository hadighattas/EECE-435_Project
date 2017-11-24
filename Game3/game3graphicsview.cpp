/**
 * \file graphics3view.cpp
 * \brief Setting up the GraphicsViews
*/
#include "game3graphicsview.h"

Game3GraphicsView::Game3GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

}

void Game3GraphicsView::setDifficulty(int diff) {
    this->difficulty = diff;
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    Game3Scene *scene = new Game3Scene;
    scene->setStackedWidget(q);
    scene->setDifficulty(difficulty);
    setScene(scene);
    show();
}

void Game3GraphicsView::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}
