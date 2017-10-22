#include "obstacle.h"

Obstacle::Obstacle(QObject *parent) :
    QObject(parent)
{
    int random_number = rand()%3;
    if (random_number == 0)
        setPixmap((QPixmap("Shape7-500.png")).scaled(75,75));
    else if (random_number == 1)
        setPixmap((QPixmap("Shape8-500left.png")).scaled(75,75));
    else if (random_number == 2)
        setPixmap((QPixmap("Shape8-500right.png")).scaled(75,75));

    setIdentity(random_number);
}

void Obstacle::setIdentity(int id) {
    this->identity = id;
}

int Obstacle::getIdentity() {
    return identity;
}
