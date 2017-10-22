#include "obstacle.h"

Obstacle::Obstacle(QObject *parent) :
    QObject(parent)
{
    srand (time(NULL));
    int random_number = rand()%4;
    if (random_number == 0)
        setPixmap((QPixmap("Shape7-500.png")).scaled(75,75));
    else if (random_number == 1)
        setPixmap((QPixmap("Shape8-500left.png")).scaled(75,75));
    else if (random_number == 2)
        setPixmap((QPixmap("Shape8-500right.png")).scaled(75,75));
    else if (random_number == 4)
        setPixmap((QPixmap("Shape7-500.png")).scaled(75,75));

    setIdentity(random_number);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);
}

void Obstacle::setIdentity(int id) {
    this->identity = id;
}

int Obstacle::getIdentity() {
    return identity;
}

void Obstacle::move() {
    int x1=10;
    if (difficulty == 0)
        x1 = 10;
    else if (difficulty == 1)
        x1 = 15;
    else if (difficulty == 2)
        x1 = 20;
    if (scene()->collidingItems(this).length() != 0){
        scene()->removeItem(this);
        delete (this);
    }
    if (y() == 65 || y() == 235 || y() == 405) {
        setPos(x() - x1, y());
    }
    else if (y() == 150 || y() == 320 || y() == 490)
        setPos(x() + x1, y());
    if (x() < -85 || x() > 1280) {
        scene()->removeItem(this);
        delete (this);
    }

}

