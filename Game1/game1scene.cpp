#include "game1scene.h"
#include "character.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

Game1Scene::Game1Scene(QObject *parent) :
    QGraphicsScene(parent)
{   
    setBackgroundBrush(QBrush(QImage("game1background.png").scaledToHeight(661).scaledToWidth(1280)));
    setSceneRect(0,0,1280,661);




}

void Game1Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    character->setDifficulty(difficulty);
    addItem(character);
    character->setPos(623, 0);
}
