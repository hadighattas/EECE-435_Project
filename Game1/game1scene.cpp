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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(newObstacle()));
    timer->start(1500);

    timeLeft = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);
    countTime = 60;

    timeText = new QGraphicsTextItem("Time left: 60");
    timeText->setPos(0, 0);
    timeText->setDefaultTextColor(QColor(Qt::white));
  //  QFont *font = new QFont("lucida", 20, QFont::Bold, FALSE);
    timeText->setFont(QFont("asap condensed", 15, QFont::Bold, false));
    timeText->document()->setPageSize(QSizeF(100,40));
    addItem(timeText);

}

void Game1Scene::setDifficulty(int diff) {
    this->difficulty = diff;
    character->setDifficulty(difficulty);
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();
    addItem(character);
    character->setPos(623, 0);

}
void Game1Scene::newObstacle(){
//    std::default_random_engine generator;
//    std::uniform_int_distribution<int> distribution(0,7);
//    int x=distribution(generator);
    ObstacleGroup *obstacle = new ObstacleGroup;
    srand (time(NULL));
    int id = obstacle->getIdentity();
    int y1=55;
    if (id == 1 ) {
        int r = rand()%4;
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
        int r = rand()%4;
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
        int r = rand()%8;
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
}

void Game1Scene::addAcquired(QString element){
    acquired+=element;
}

void Game1Scene::updateTimer() {
    countTime--;
    if (countTime==0)
        endGame();
    timeText->setPlainText("Time left: " + QVariant(countTime).toString());

}

void Game1Scene::endGame() {

}
