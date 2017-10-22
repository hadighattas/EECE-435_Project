/**
 * \file character.cpp
 * \brief Character Functionalities
 *
 * Setting the image of the character according to level of difficulty.\n
 * Implementing movement of the character.\n
*/

#include "character.h"

Character::Character(QObject *parent) :
    QObject(parent)
{

}
/**
 * @brief Character::setDifficulty
 * @param diff
 */
void Character::setDifficulty(int diff) {
    this->difficulty = diff;
    if (difficulty == 0) {
        setPixmap((QPixmap("Shape4-55.png")).scaled(55,55));
    }
    else if (difficulty == 1) {
        setPixmap((QPixmap("Shape5-55.png")).scaled(55,55));
    }
    else if (difficulty == 2) {
        setPixmap((QPixmap("Shape6-55.png")).scaled(55,55));
    }
}

/**
 * @brief Character::keyPressEvent
 * @param event
 */
void Character::keyPressEvent(QKeyEvent *event) {
    /**
    * Move up, down, right or left according to key press even.\n
    * Move up or down: only by increments of 65 (60 the first time).\n
    * Move right or left: continuously without exceeding bounds.\n
    */
    if (event->key() == Qt::Key_Right) {
        if (x() == 1233)
            ;
        else
            setPos(x()+10, y());
    }

    else if (event->key() == Qt::Key_Left) {
        if (x() == 3)
            ;
        else
            setPos(x()-10, y());
    }

    else if (event->key() == Qt::Key_Up) {
        if (y() == 0)
            ;
        else if (y() == 60)
            setPos(x(), 0);
        else
            setPos(x(), y()-65);
    }

    else if (event->key() == Qt::Key_Down) {
        if (y() == 580)
            ;
        else if (y() == 0)
            setPos(x(), y()+60);
        else
            setPos(x(), y()+65);
    }
}


