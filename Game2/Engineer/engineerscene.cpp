/**
 * \file engineerscene.cpp
 * \brief Main scene that shows progress of character
 *
 * Shows the progress of the character on map.\n
 * Shows current amount of money.\n
 * Allows character to pass from scenario to scenario.\n
 * When all scenarios completed, allows to switch to score menu.\n
*/

#include "engineerscene.h"

EngineerScene::EngineerScene(QObject *parent) :
    QGraphicsScene(parent)
{
    stateOfEngineer = 0;
    moneyGlobal = 10000;
    setBackgroundBrush(QBrush(QImage(":/images2/SpaceBackground.png").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0, 0, 1280, 720);

    //adding character on map
    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape11-400.png").scaled(55, 55, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(370, 320);
    addItem(character);

    arrow = new QGraphicsPixmapItem((QPixmap(":/images2/arrow.png")));
    arrow->setPos(955, 510);
    addItem(arrow);
    flag = true;

    if (stateOfEngineer == 0)
        next = new QGraphicsTextItem("START");
    else
        next = new QGraphicsTextItem("NEXT");
    next->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    next->setPos(965, 543);
    next->setRotation(9);
    next->setDefaultTextColor(QColor(Qt::black));
    next->setFont(QFont("asap condensed", 14, QFont::Bold, false));
    addItem(next);

    //showing current amount of money
    money = new QGraphicsTextItem("Money:\n    10000 Vollars");
    money->setPos(1060, 150);
    money->setDefaultTextColor(QColor(Qt::yellow));
    money->setFont(QFont("asap condensed", 16, QFont::Bold, false));
    addItem(money);

    //showing time of day
    time = new QGraphicsTextItem("00:00:00");
    time->setPos(230, 550);
    time->setRotation(-5);
    time->setDefaultTextColor(QColor(Qt::yellow));
    time->setFont(QFont("asap condensed", 18, QFont::Bold, false));
    time->setPlainText(QTime::currentTime().toString());
    addItem(time);

    exit = new QGraphicsTextItem("EXIT");
    exit->setPos(1000, 650);
    exit->setDefaultTextColor(QColor(Qt::white));
    exit->setFont(QFont("asap condensed", 18, QFont::Bold, false));
    addItem(exit);

    timerTime = new QTimer(this);
    connect(timerTime, SIGNAL(timeout()), this, SLOT(updateTime()));
    timerTime->start(500);

    QSound::play(":/sounds/ComputerSciFi.wav");

    updateTime();

    //initial values
    friendship = 3;
    compliance = 3;
    honesty = 3;
    forgivingness = 3;
    helping = 3;
    family = 3;
    courage = 3;

    stateOfDoctor = 0;
    stateOfEngineer = 0;
}

/**
 * @brief EngineerScene::setStackedWidget
 * @param stack
 */
void EngineerScene::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

/**
 * @brief EngineerScene::mousePressEvent
 * @param event
 */
void EngineerScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on arrow, this function takes him to next scenario.\n
     * After the last scenario, takes him to score ui.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if ((item == next || item == arrow) && stateOfEngineer == 0) {
        FirstSceneEngineer *first = new FirstSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(first);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 1) {
        SecondSceneEngineer *second = new SecondSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(second);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 2) {
        ThirdSceneEngineer *third = new ThirdSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(third);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 3) {
        FourthSceneEngineer *fourth = new FourthSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(fourth);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 4) {
        FifthSceneEngineer *fifth = new FifthSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(fifth);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 5) {
        SixthSceneEngineer *sixth = new SixthSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(sixth);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 6) {
        SeventhSceneEngineer *seventh = new SeventhSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(seventh);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 7) {
        EigthSceneEngineer *eigth = new EigthSceneEngineer(this);
        QGraphicsView *view = views().at(0);
        view->setScene(eigth);
    }
    else if ((item == next || item == arrow) && stateOfEngineer == 8) {
        stateOfEngineer = 0;
        moneyGlobal = 10000;
        score = new Game2Score;
        timerTime->stop();
        score->setStackedWidget(q);
        q->addWidget(score);
        q->setCurrentWidget(score);
        game2Index = 100;
        clear();
        deleteLater();
    }
    else if (item == exit) {
        q->setCurrentIndex(mainIndex);
        q->show();
    }
}

/**
 * @brief EngineerScene::updateTime
 */
void EngineerScene::updateTime(){
    /**
     * Shows the time of day, updated every second.\n
     * Depending on value of stateOfEngineer, which is global, sets position of character on the map.\n
    */
    time->setPlainText(QTime::currentTime().toString());
    if (flag == true) {
        arrow->setPixmap((QPixmap(":/images2/arrowGlow.png")));
        flag = false;
    }
    else {
        arrow->setPixmap((QPixmap(":/images2/arrow.png")));
        flag = true;
    }

    money->setPlainText("Money:\n   " + QString::number(moneyGlobal) + " Vollars");

    if (stateOfEngineer == 1) {
        character->setPos(425, 300);
        next->setPlainText("NEXT");
    }
    else if (stateOfEngineer == 2)
        character->setPos(480, 280);
    else if (stateOfEngineer == 3)
        character->setPos(535, 260);
    else if (stateOfEngineer == 4)
        character->setPos(590, 245);
    else if (stateOfEngineer == 5)
        character->setPos(645, 225);
    else if (stateOfEngineer == 6)
        character->setPos(700, 205);
    else if (stateOfEngineer == 7)
        character->setPos(755, 190);
    else if (stateOfEngineer == 8) {
        character->setPos(810, 175);
        next->setPlainText("FINISH");
    }
}
