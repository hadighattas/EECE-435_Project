/**
 * \file obstaclegroup.cpp
 * \brief Groups a value with an obstacle
 *
 * Creating lists of values and vices.\n
 * Grouping values with obstacles.\n
 * Moving groups.\n
*/

#include "obstaclegroup.h"

ObstacleGroup::ObstacleGroup(QObject *parent) :
    QObject(parent)
{
    /**
     * Generating a random value from 2 lists: values and vices.\n
     * Goruping the value (label) with an obstacle.\n
    */
    srand(time(NULL));
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);

    setIdentity(obs->getIdentity());
    addToGroup(obs);

    int r1 = rand()%2;
    if (r1==0) {
        int r2 = rand() % (globalValues.length());
        label = new QGraphicsTextItem(globalValues.value(r2));
        type=true;
    }
    else {
        int r2 = rand() % (globalVices.length());
        label = new QGraphicsTextItem(globalVices.value(r2));
        type=false;
    }

    label->setDefaultTextColor(QColor(Qt::white));
    addToGroup(label);


}

/**
 * @brief ObstacleGroup::move
 */
void ObstacleGroup::move() {
    /**
     * Speed increments as difficulty increases.\n
     * Move group left or right according to lane it is in.\n
     * Detecting collisions and adding catched values in output files: values and vices.\n
     * Removing groups when they exceed bounds.\n
    */
    int x1=10;
    if (difficulty == 0)
        x1 = 10;
    else if (difficulty == 1)
        x1 = 15;
    else if (difficulty == 2)
        x1 = 20;

    if (scene()->collidingItems(label).length()>0){
        QGraphicsItem *item = scene()->collidingItems(label).takeAt(0);
        QGraphicsTextItem *groupTemp = dynamic_cast<QGraphicsTextItem*>(item);
        if (groupTemp != 0) {
            scene()->removeItem(this);
            delete this;
        }
    }
    if (y() == 55 || y() == 185 || y()==315||y() == 445) {
        setPos(x() - x1, y());
    }
    else
        setPos(x() + x1, y());
    if (x() < -500|| x() > 2000) {
        scene()->removeItem(this);
        delete (this);
    }

}

QString ObstacleGroup::getText() {
    return label->toPlainText();
}

bool ObstacleGroup::getType() {
    return type;
}

int ObstacleGroup::getIdentity() {
    return identity;
}

void ObstacleGroup::setIdentity(int id) {
    identity = id;
}

QGraphicsTextItem * ObstacleGroup::getLabel(){
    return label;
}