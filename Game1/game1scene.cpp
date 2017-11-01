/**
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
    ofstream values;
    values.open("values.txt", fstream::out| fstream::trunc);
    values.close();
    ofstream vices;
    vices.open("vices.txt", fstream::out| fstream::trunc);
    vices.close();
    setBackgroundBrush(QBrush(QImage("game1background.png").scaledToHeight(661).scaledToWidth(1280)));
    setSceneRect(0,0,1280,661);

    timerObstacle = new QTimer(this);
    connect(timerObstacle, SIGNAL(timeout()), this, SLOT(newObstacle()));
    timerObstacle->start(700);

    timeLeft = new QTimer(this);
    connect(timeLeft, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timeLeft->start(1000);
    countTime = 60;

    timerFrame = new QTimer(this);
    connect(timerFrame, SIGNAL(timeout()), this, SLOT(updateLives()));
    timerFrame->start(200);

    human = new QGraphicsPixmapItem((QPixmap("Shape9-500.png")).scaled(75, 75));
    human->setPos(623, 586);
    addItem(human);

    timeText = new QGraphicsTextItem("Time left: 60");
    timeText->setPos(0, 0);
    timeText->setDefaultTextColor(QColor(Qt::white));
    timeText->setFont(QFont("asap condensed", 15, QFont::Bold, false));
    timeText->document()->setPageSize(QSizeF(100,40));
    addItem(timeText);
    for(int i = 0; i < 3; i++){
        QGraphicsPixmapItem *life = new QGraphicsPixmapItem(QPixmap("Shape10-50.png"));
        life->setPos(150 + 60*i, 0);
        addItem(life);
    }
    distribution=std::uniform_int_distribution<int>(0, 7);


}

void Game1Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    character->setDifficulty(difficulty);
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();
    addItem(character);
    character->setPos(623, 0);

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

    int r1=distribution(generator);
    ObstacleGroup *obstacle = new ObstacleGroup;

    srand (time(0));
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
            y1=445;
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
        obstacle->setPos(1140, y1);
    }
    else if (id == 2)
        obstacle->setPos(0, y1);
    else {
        if(y1==55|| y1==185 || y1==315 || y1==445){
            obstacle->setPos(1140,y1);
        }
        else obstacle->setPos(0,y1);
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

}

void Game1Scene::endGame() {

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
    if (livesCount < 7) {
        if(character->getValues()->size() > valuesNumber){
            QGraphicsPixmapItem *life = new QGraphicsPixmapItem(QPixmap("Shape10-50.png"));
            life->setPos(150 + 60*(livesCount), 0);
            livesCount++;
            addItem(life);
            valuesNumber++;
        }
        if(character->getVices()->size() > vicesNumber){
            livesCount--;
            QGraphicsItem *toDelete = itemAt(160 + 60*(livesCount), 10, QTransform());
            removeItem(toDelete);
            delete toDelete;
            vicesNumber++;
            character->setPos(623,0);
        }
    }
    if (livesCount == 0)
        endGame();

}
