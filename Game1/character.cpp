#include "character.h"

Character::Character(QObject *parent) :
    QObject(parent)
{

}

void Character::setDifficulty(int diff) {
    this->difficulty = diff;
    if (difficulty == 0) {
        setPixmap((QPixmap("Shape4-500.png")).scaled(55,55));
    }
    else if (difficulty == 1) {
        setPixmap((QPixmap("Shape5-500.png")).scaled(50,50));
    }
    else if (difficulty == 2) {
        setPixmap((QPixmap("Shape6-500.png")).scaled(50,50));
    }
}
