#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include "character.h"
#include <stdlib.h>
#include <QObject>
#include <QImage>
#include <QBrush>
#include "obstacle.h"
#include <time.h>
#include <QStringList>
#include <fstream>

using namespace std ;

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Scene(QObject *parent = 0);
    void setDifficulty(int diff);
    void addAcquired(QString element);
    void endGame();


signals:

public slots:
    void newObstacle();
    void updateTimer();

private:
    int difficulty;
    Character *character = new Character;
    QTimer *timer;
    QTimer *timeLeft;
    QStringList acquired;
    int countTime;
    QGraphicsTextItem *timeText;
};

#endif // GAME1SCENE_H
