﻿/**
 * \file game1scene.cpp
 * \brief Adding and managing scene items
 *
 * Setting the background, adding the obstacles and updating the number of lives.\n
*/

#include "game1scene.h"
#include "character.h"
#include "obstaclegroup.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLabel>
#include <QGraphicsLinearLayout>
#include <QTextDocument>

Game1Scene::Game1Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/Game1Background.jpg").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0, 0, 1280, 720);

    blurr = new QGraphicsPixmapItem(QPixmap(":/images2/Game1BackgroundBlurred.jpg").scaled(1280, 720));
    blurr->setPos(1,1);
    blurr->setZValue(20);
    addItem(blurr);

    startCounter = new QGraphicsTextItem("5");
    startCounter->setPos(600, 300);
    startCounter->setZValue(20);
    startCounter->setDefaultTextColor(QColor(Qt::white));
    startCounter->setFont(QFont("asap condensed", 100, QFont::Bold, false));
    startCounter->document()->setPageSize(QSizeF(300,300));
    addItem(startCounter);

    timerStart = new QTimer(this);
    connect(timerStart, SIGNAL(timeout()), this, SLOT(start()));

    timerObstacle = new QTimer(this);
    connect(timerObstacle, SIGNAL(timeout()), this, SLOT(newObstacle()));

    timeLeft = new QTimer(this);
    connect(timeLeft, SIGNAL(timeout()), this, SLOT(updateTimer()));
    countTime = 60;

    timerFrame = new QTimer(this);
    connect(timerFrame, SIGNAL(timeout()), this, SLOT(updateLives()));

    human = new QGraphicsPixmapItem((QPixmap(":/images2/Shape9-75.png")).scaled(75, 75));
    human->setPos(623, 586);
    addItem(human);

    timeText = new QGraphicsTextItem("Time left: 60");
    timeText->setPos(0, 0);
    timeText->setDefaultTextColor(QColor(Qt::white));
    timeText->setFont(QFont("asap condensed", 15, QFont::Bold, false));
    timeText->document()->setPageSize(QSizeF(100,40));
    addItem(timeText);

    numAcquired = new QGraphicsTextItem("Values: 0          Vices: 0   ");
    numAcquired->setPos(1100, 0);
    numAcquired->setDefaultTextColor(QColor(Qt::white));
    numAcquired->setFont(QFont("asap condensed", 15, QFont::Bold, false));
    numAcquired->document()->setPageSize(QSizeF(500,40));
    addItem(numAcquired);

    exit = new QGraphicsTextItem("EXIT");
    exit->setPos(1000, 650);
    exit->setDefaultTextColor(QColor(Qt::white));
    exit->setFont(QFont("asap condensed", 18, QFont::Bold, false));
    addItem(exit);

    for(int i = 0; i < 3; i++){
        QGraphicsPixmapItem *life = new QGraphicsPixmapItem(QPixmap(":/images2/Shape10-50.png"));
        life->setPos(150 + 60*i, 0);
        addItem(life);
    }
    distribution=std::uniform_int_distribution<int>(0, 7);

    distribution1=std::uniform_int_distribution<int>(0, 100);
    newObstacle();
}

void Game1Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    character->started = false;
    character->setDifficulty(difficulty);
    addItem(character);
    character->setPos(623, 0);
    timerObstacle->start(200+25*(difficulty+1));
    timeLeft->start(1000);
    timerFrame->start(400);
    timerStart->start(1000);
}

void Game1Scene::start() {
    startCount--;
    if(startCount > 0) {
        startCounter->setPlainText(QString::number(startCount));
    }
    if (startCount == 0){
        removeItem(startCounter);
        removeItem(blurr);
        character->setFlag(QGraphicsItem::ItemIsFocusable);
        character->setFocus();
        timerStart->stop();
        character->started = true;
    }
}

/**
 * @brief Game1Scene::newObstacle
 */
void Game1Scene::newObstacle(){
    /**
     * Setting position of obstacle randomly.\n
     * id = 0 or 3 --> flying saucer, can be added left or right.\n
     * id = 1 --> space shuttle oriented to left, can be added only starting at right position.\n
     * id = 2 --> space shuttle oriented to right, can be added only starting at left position.\n
    */
    obstaclescreated++;
    int r1 = distribution(generator);
    int r2 = distribution1(generator1);
    distribution1(generator1);
    ObstacleGroup *obstacle = new ObstacleGroup;
    obstacle->setDifficulty(difficulty);
    obstacle->setRand(r2);
    int id = obstacle->getIdentity();
    int y1=55;
    if (id == 1 ) {
        int r = r1%4;
        if (r == 0)
            y1 = 55;
        else if (r == 1)
            y1 = 185;
        else if (r == 2)
            y1 = 315;
        else if (r== 3)
            y1 = 445;
    }
    else if (id == 2 ) {
        int r = r1%4;
        if (r == 0)
            y1 = 120;
        else if (r == 1)
            y1 = 250;
        else if (r == 2)
            y1 = 380;
        else if (r==3)
            y1 = 510;
    }
    else if (id == 0 || id== 3 ) {
        int r = r1%8;
        if (r == 0)
            y1 = 55;
        else if (r == 1)
            y1 = 120;
        else if (r == 2)
            y1 = 185;
        else if (r == 3)
            y1 = 250;
        else if (r == 4)
            y1 = 315;
        else if (r == 5)
            y1 = 380;
        else if(r==6)
            y1=445;
        else if(r==7)
            y1=510;

    }
    if (id == 1) {
        obstacle->setPos(xright, y1);
    }
    else if (id == 2)
        obstacle->setPos(xleft, y1);
    else {
        if(y1==55|| y1==185 || y1==315 || y1==445){
            obstacle->setPos(xright,y1);
        }
        else obstacle->setPos(xleft,y1);
    }
    addItem(obstacle);
    if (collidingItems(obstacle->getLabel()).length()>0){
        QGraphicsItem *item = collidingItems(obstacle->getLabel()).takeAt(0);
        QGraphicsTextItem *groupTemp = dynamic_cast<QGraphicsTextItem*>(item);
        if (groupTemp != 0) {
            removeItem(obstacle);
            delete obstacle;
        }
    }
    if(obstaclescreated==15){
        timerObstacle->setInterval(500);
        xleft=-200;
        xright=1400;
    }
}


/**
 * @brief Game1Scene::updateTimer
 */
void Game1Scene::updateTimer() {
    /**
     * countTime counts the number of times timer has expired (initalized to 60).\n
     * When countTime reaches 0 or when character reaches bottom of page --> end game.\n
    */
    countTime--;
    if (character->y() == 580)
        endGame();
    if (countTime==0)
        endGame();
    timeText->setPlainText("Time left: " + QVariant(countTime).toString());
    if (character->y() == 580){
        character->setPos(623,580);
        endGame();
    }

}

void Game1Scene::endGame() {
    timerFrame->stop();
    timerObstacle->stop();
    timeLeft->stop();
    Game1Score *game1score = new Game1Score;
    game1score->setScore(livesCount, countTime, character->getValues(), character->getVices());
    game1score->setStackedWidget(q);
    q->addWidget(game1score);
    q->setCurrentWidget(game1score);
    game1Index = 100;
    deleteLater();
}

/**
 * @brief Game1Scene::updateLives
 */
void Game1Scene::updateLives() {
    /**
     * Updating the live items on scene.\n
     * lives is a List of live images.\n
     * When function is called, remove exisiting images and pritn new ones equal to number of current lives.\n
    */
    character->checkCollisions();
    if (livesCount < 6) {
        if(character->getValues()->size() > valuesNumber){
            QGraphicsPixmapItem *life = new QGraphicsPixmapItem(QPixmap(":/images2/Shape10-50.png"));
            life->setPos(150 + 60*(livesCount), 0);
            livesCount++;
            addItem(life);
            valuesNumber++;
        }
    }
        if(character->getVices()->size() > vicesNumber){
            livesCount--;
            QGraphicsItem *toDelete = itemAt(160 + 60*(livesCount), 10, QTransform());
            removeItem(toDelete);
            delete toDelete;
            vicesNumber++;
            character->setPos(623,0);
        }
        numAcquired->setPlainText("Values: " + QString::fromUtf8(std::to_string(valuesNumber).c_str()) + "          Vices: " + QString::fromUtf8(std::to_string(vicesNumber).c_str()) + "   ");

    if (livesCount == 0)
        endGame();
}

void Game1Scene::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

void Game1Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item == exit) {
            timeLeft->stop();
            timerFrame->stop();
            timerObstacle->stop();
            character->setPos(623, 0);
            q->setCurrentIndex(mainIndex);
            character->started = false;
        }
    }
}

void Game1Scene::resume() {
    character->started = true;
    timeLeft->start(1000);
    timerFrame->start(400);
    timerObstacle->start(200);
}
