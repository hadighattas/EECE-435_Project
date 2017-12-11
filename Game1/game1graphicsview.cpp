/**
 * \file graphics1view.cpp
 * \brief Setting up the GraphicsViews
*/
#include "game1graphicsview.h"


Game1GraphicsView::Game1GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene1 = new Game1Scene;
}

void Game1GraphicsView::setDifficulty(int diff) {
    this->difficulty = diff;
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    scene1->setStackedWidget(q);
    scene1->setDifficulty(difficulty);
    setScene(scene1);
    show();
}

void Game1GraphicsView::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

void Game1GraphicsView::resume() {
    scene1->resume();
}

Game1Scene *Game1GraphicsView::getScene() {
    return scene1;
}
