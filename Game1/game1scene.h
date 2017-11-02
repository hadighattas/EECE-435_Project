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
    void updateScore();

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
    QGraphicsTextItem *scoreText;
    QGraphicsPixmapItem *human;
    int valuesNumber=0;
    int vicesNumber=0;
    int livesCount=3;
    int score=1000;
    int xleft=0, xright=1150;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    std::default_random_engine generator1;
    std::uniform_int_distribution<int> distribution1;
    int obstaclescreated=0;
};

#endif // GAME1SCENE_H
