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
#include "obstaclegroup.h"
#include "game1score.h"
#include <QWidget>
#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>

#include "../globalindices.h"

using namespace std ;

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Scene(QObject *parent = 0);
    void setDifficulty(int diff);
    void addAcquired(QString element);
    void endGame();
    void updateAcquired();
    void setStackedWidget(QStackedWidget *stack);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void resume();

signals:

public slots:
    void newObstacle();
    void updateTimer();
    void updateLives();
    void start();

private:
    int difficulty;
    Character *character = new Character;
    QTimer *timerObstacle;
    QTimer *timeLeft;
    QTimer *timerFrame;
    QTimer *timerStart;
    int countTime;
    QGraphicsTextItem *timeText, *exit, *startCounter;
    QGraphicsPixmapItem *human;
    QGraphicsPixmapItem *blurr;
    QGraphicsTextItem *numAcquired;
    int valuesNumber=0;
    int vicesNumber=0;
    int livesCount=3;
    int startCount=5;
    int xleft=0, xright=1200;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    std::default_random_engine generator1;
    std::uniform_int_distribution<int> distribution1;
    int obstaclescreated=0;
    QStackedWidget *q;
};

#endif // GAME1SCENE_H
