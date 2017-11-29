/**
 * \file graphics3view.cpp
 * \brief Setting up the GraphicsViews
*/
#include "game3graphicsview.h"

Game3GraphicsView::Game3GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

}

/**
 * @brief Game3GraphicsView::setDifficulty
 * @param diff
 */
void Game3GraphicsView::setDifficulty(int diff) {
    /**
      * Passing difficulty to scene\n
      * Showing the scene\n
      */
    this->difficulty = diff;
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    Game3Scene *scene = new Game3Scene;
    scene->setStackedWidget(q, this->menuIndex);
    scene->setDifficulty(difficulty);
    setScene(scene);
    show();
}

void Game3GraphicsView::setStackedWidget(QStackedWidget *stack, int menuIndex) {
    this->q = stack;
    this->menuIndex = menuIndex;
}
