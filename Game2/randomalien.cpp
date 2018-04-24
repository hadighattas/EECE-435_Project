#include "randomalien.h"

RandomAlien::RandomAlien(QObject *parent) :
    QObject(parent)
{
    randomNumber = rand()%3;
    if (randomNumber == 0)
        setPixmap(QPixmap(":/images2/Shape4-150.png"));
    else if (randomNumber == 1)
        setPixmap(QPixmap(":/images2/Shape5-150.png"));
    else if (randomNumber == 2)
        setPixmap(QPixmap(":/images2/Shape6-150.png"));
}
