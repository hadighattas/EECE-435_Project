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
}

void Obstacle::setIdentity(int id) {
    this->identity = id;
    if (identity == 0)
        setPixmap((QPixmap(":/images2/Shape7-65.png")));
    else if (identity == 1)
        setPixmap((QPixmap(":/images2/Shape8-65left.png")));
    else if (identity == 2)
        setPixmap((QPixmap(":/images2/Shape8-65right.png")));
    else if (identity == 3)
        setPixmap((QPixmap(":/images2/Shape7-65.png")));
}

int Obstacle::getIdentity() {
    return identity;
}

