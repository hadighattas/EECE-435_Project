/**
 * \file player.cpp
 * \brief Defining functionalities of the player.
*/

#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{

}

/**
 * @brief Character::setDifficulty
 * @param diff
 */
void Player::setDifficulty(int diff) {
    /**
     *
     */
    this->difficulty = diff;
    if (difficulty == 0) {
        setPixmap((QPixmap(":/images2/Shape4-150.png")).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (difficulty == 1) {
        setPixmap((QPixmap(":/images2/Shape5-150.png")).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (difficulty == 2) {
        setPixmap((QPixmap(":/images2/Shape6-150.png")).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void Player::move(QKeyEvent *event) {
    if  (event->key() == Qt::Key_Right) {
        if (x() == 1040)
            ;
        else setPos(x() + 180, y());
    }
    else if (event->key() == Qt::Key_Left) {
        if (x() == 140)
            ;
        else setPos(x() - 180, y());
    }
    else if  (event->key() == Qt::Key_Up) {
        if (y() == 167)
            ;
        else setPos(x(), y() - 226);
    }
    else if (event->key() == Qt::Key_Down) {
        if (y() == 619)
            ;
        else setPos(x(), y() + 226);
    }

}
