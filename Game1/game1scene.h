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
#include "obstaclegroup.h"

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
    void updateLives();

private:
    int difficulty;
    Character *character = new Character;
    QTimer *timerObstacle;
    QTimer *timeLeft;
    QTimer *timerFrame;
    int countTime;
    QGraphicsTextItem *timeText;
    QGraphicsPixmapItem *human;
    int valuesNumber=0;
    int vicesNumber=0;
    int livesCount=3;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;



};

#endif // GAME1SCENE_H
