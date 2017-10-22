/**
 * \file obstacle.cpp
 * \brief Creating obstacles
 *
 * Determing type of obstacle (space shuttle or flying saucer) randomly.\n
*/

#include "obstacle.h"

Obstacle::Obstacle(QObject *parent) :
    QObject(parent)
{
    srand (time(NULL));
    int random_number = rand()%4;
    if (random_number == 0)
        setPixmap((QPixmap("Shape7-75.png")));
    else if (random_number == 1)
        setPixmap((QPixmap("Shape8-75left.png")));
    else if (random_number == 2)
        setPixmap((QPixmap("Shape8-75right.png")));
    else if (random_number == 3)
        setPixmap((QPixmap("Shape7-75.png")));

    setIdentity(random_number);

}

void Obstacle::setIdentity(int id) {
    this->identity = id;
}

int Obstacle::getIdentity() {
    return identity;
}
