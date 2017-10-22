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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newObstacle()));
    timer->start(1000);
}

void Game1Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    character->setDifficulty(difficulty);
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();
    addItem(character);
    character->setPos(623, 0);
    newObstacle();
    newObstacle();
    newObstacle();
}
void Game1Scene::newObstacle(){
    Obstacle *obstacle = new Obstacle;
    srand (time(NULL));
    int id = obstacle->getIdentity();
    int y1=65;
    if (id == 1 ) {
        int r = rand()%3;
        if (r == 0)
            y1 = 65;
        else if (r == 1)
            y1 = 235;
        else if (r == 2)
            y1 = 405;
    }
    else if (id == 2 ) {
        int r = rand()%3;
        if (r == 0)
            y1 = 150;
        else if (r == 1)
            y1 = 320;
        else if (r == 2)
            y1 = 490;
    }
    else if (id == 0 ) {
        int r = rand()%6;
        if (r == 0)
            y1 = 65;
        else if (r == 1)
            y1 = 150;
        else if (r == 2)
            y1 = 235;
        else if (r == 3)
            y1 = 320;
        else if (r == 4)
            y1 = 405;
        else if (r == 5)
            y1 = 495;
    }
    if (id == 1) {
        obstacle->setPos(1200, y1);
    }
    else if (id == 2)
        obstacle->setPos(0, y1);
    else {
        if(y1==65 || y1==235 || y1==405){
            obstacle->setPos(1200,y1);
        }
        else obstacle->setPos(0,y1);
    }

    addItem(obstacle);
}

