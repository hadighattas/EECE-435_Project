/**
 * \file doctorscene.cpp
 * \brief Main scene that shows progress of character
 *
 * Shows the progress of the character on map.\n
 * Shows current amount of money.\n
 * Allows character to pass from scenario to scenario.\n
 * When all scenarios completed, allows to switch to score menu.\n
*/

#include "doctorscene.h"

DoctorScene::DoctorScene(QObject *parent) :
    QGraphicsScene(parent)
{
    stateOfDoctor = 0;
    moneyGlobal = 10000;
    setBackgroundBrush(QBrush(QImage("SpaceBackground.png").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0, 0, 1280, 720);

    //adding character on map
    character = new QGraphicsPixmapItem(QPixmap("Shape12-400.png").scaled(55, 55, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(370, 320);
    addItem(character);

    arrow = new QGraphicsPixmapItem((QPixmap("arrow.png")));
    arrow->setPos(955, 510);
    addItem(arrow);
    flag = true;

    if (stateOfDoctor == 0)
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
    time = new QGraphicsTextItem("10:00:20");
    time->setPos(230, 550);
    time->setRotation(-5);
    time->setDefaultTextColor(QColor(Qt::yellow));
    time->setFont(QFont("asap condensed", 18, QFont::Bold, false));
    time->setPlainText(QTime::currentTime().toString());
    addItem(time);

    timerTime = new QTimer(this);
    connect(timerTime, SIGNAL(timeout()), this, SLOT(updateTime()));
    timerTime->start(500);

    QSound::play("ComputerSciFi.wav");

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
 * @brief DoctorScene::mousePressEvent
 * @param event
 */
void DoctorScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on arrow, this function takes him to next scenario.\n
     * After the last scenario, takes him to score ui.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if ((item == next || item == arrow) && stateOfDoctor == 0) {
        FirstSceneDoctor *first = new FirstSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(first);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 1) {
        SecondSceneDoctor *second = new SecondSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(second);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 2) {
        ThirdSceneDoctor *third = new ThirdSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(third);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 3) {
        FourthSceneDoctor *fourth = new FourthSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(fourth);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 4) {
        FifthSceneDoctor *fifth = new FifthSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(fifth);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 5) {
        SixthSceneDoctor *sixth = new SixthSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(sixth);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 6) {
        SeventhSceneDoctor *seventh = new SeventhSceneDoctor(this);
        QGraphicsView *view = views().at(0);
        view->setScene(seventh);
    }
    else if ((item == next || item == arrow) && stateOfDoctor == 8) {
        stateOfDoctor = 0;
        moneyGlobal = 10000;
        score = new Game2Score;
        timerTime->stop();
        score->setStackedWidget(q);
        q->addWidget(score);
        q->setCurrentWidget(score);
        clear();
        deleteLater();
    }
}

/**
 * @brief DoctorScene::setStackedWidget
 * @param stack
 */
void DoctorScene::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

/**
 * @brief DoctorScene::updateTime
 */
void DoctorScene::updateTime(){
    /**
     * Shows the time of day, updated every second.\n
     * Depending on value of stateOfEngineer, which is global, sets position of character on the map.\n
    */
    time->setPlainText(QTime::currentTime().toString());
    if (flag == true) {
        arrow->setPixmap((QPixmap("arrowGlow.png")));
        flag = false;
    }
    else {
        arrow->setPixmap((QPixmap("arrow.png")));
        flag = true;
    }

    money->setPlainText("Money:\n   " + QString::number(moneyGlobal) + " Vollars");

    if (stateOfDoctor == 1) {
        character->setPos(425, 300);
        next->setPlainText("NEXT");
    }
    else if (stateOfDoctor == 2)
        character->setPos(480, 280);
    else if (stateOfDoctor == 3)
        character->setPos(535, 260);
    else if (stateOfDoctor == 4)
        character->setPos(590, 245);
    else if (stateOfDoctor == 5)
        character->setPos(645, 225);
    else if (stateOfDoctor == 6)
        character->setPos(700, 205);
    else if (stateOfDoctor == 7)
        character->setPos(755, 190);
    else if (stateOfDoctor == 8) {
        character->setPos(810, 175);
        next->setPlainText("FINISH");
    }
}
