#ifndef OBSTACLEGROUP_H
#define OBSTACLEGROUP_H

#include <QGraphicsItemGroup>
#include "obstacle.h"
#include <QGraphicsTextItem>
#include <QString>
#include <time.h>
#include "stdlib.h"
#include <fstream>
#include <iostream>
using namespace std;
class ObstacleGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit ObstacleGroup(QObject *parent = 0);
    void setIdentity(int id);
    int getIdentity();

signals:

public slots:
    void move();

private:
    int identity;
    int difficulty;
    Obstacle *obs = new Obstacle;
    QGraphicsTextItem *text = new QGraphicsTextItem;
    QTimer *timer = new QTimer;
    QStringList values;
    QStringList vices;
    QGraphicsTextItem *label ;
    bool type;
};

#endif // OBSTACLEGROUP_H
