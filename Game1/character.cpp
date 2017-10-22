#include "character.h"

Character::Character(QObject *parent) :
    QObject(parent)
{

}

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

void Character::keyPressEvent(QKeyEvent *event) {
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
        else if (y() == 75)
            setPos(x(), y()-75);
        else
            setPos(x(), y()-85);
    }

    else if (event->key() == Qt::Key_Down) {
        if (y() == 585)
            ;
        else if (y() == 0)
            setPos(x(), y()+75);
        else
            setPos(x(), y()+85);
    }
}


