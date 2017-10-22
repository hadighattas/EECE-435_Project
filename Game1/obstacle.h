#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <stdlib.h>
#include <time.h>
class Obstacle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Obstacle(QObject *parent = 0);
    void setDifficulty(int diff);
    void setIdentity(int id);
    int getIdentity();

signals:

public slots:
    void move();

private:
    int difficulty;
    int identity;
    QTimer *timer = new QTimer;

};

#endif // OBSTACLE_H
