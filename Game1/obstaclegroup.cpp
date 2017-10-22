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

    values<<"CARING"<<"COMMITMENT"<<"COMPASSION"<<"COURTESY"<<"HONESTY"<<"INTEGRITY"<<"OPTIMISIM"
            <<"KINDNESS"<<"OPENNESS"<<"WISDOM"<<"PEACE"<<"FORGVING";
    vices<<"JEALOUS"<<"COWARDICE"<<"ENVY"<<"SHYNESS"<<"ANGER"<<"INSENSIBILITY"<<"MEANNESS"<<
           "ARROGANCE"<<"BRAGGING"<<"WEAKNESS"<<"GREED"<<"DISLOYALTY"<<"RECKLESNESS"<<"EXTREMESIM"
           <<"DELUSION"<<"HOSTILITY"<<"LAZINESS"<<"RACISM"<<"STUPIDITY"<<"EGOISM";

    int r1 = rand()%2;
    if (r1==0) {
        int r2 = rand()%11;
        label = new QGraphicsTextItem(values.value(r2+1));
        type=true;
    }
    else {
        int r2 = rand()%19;
        label = new QGraphicsTextItem(vices.value(r2+1));
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
    if (scene()->collidingItems(this).length() >2){
        if(type){
            string value=this->label->toPlainText().toStdString();
            ofstream values;
            values.open("values.txt", ios::app);
            values<<value<<"\n";
            values.close();

        }
        else{
            string vice=this->label->toPlainText().toStdString();
            ofstream vices;
            vices.open("vices.txt", ios::app);
            vices<<vice<<"\n";
            vices.close();
        }
        scene()->removeItem(this);
        delete (this);
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
int ObstacleGroup::getIdentity(){
    return identity;
}
void ObstacleGroup::setIdentity(int id){
    this->identity=id;
}

