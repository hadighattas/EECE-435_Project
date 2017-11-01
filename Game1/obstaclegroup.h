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
#include "global.h"

using namespace std;
class ObstacleGroup : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit ObstacleGroup(QObject *parent = 0);
    QString getText();
    bool getType();
    void setIdentity(int id);
    int getIdentity();
    QGraphicsTextItem *getLabel();

signals:

public slots:
    void move();

private:
    int difficulty;
    Obstacle *obs = new Obstacle;
    QTimer *timer = new QTimer;
    QGraphicsTextItem *label;
    bool type;
    int identity;

};

#endif // OBSTACLEGROUP_H
