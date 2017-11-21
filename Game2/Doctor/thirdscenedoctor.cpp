/**
 * \file thirdscenedoctor.cpp
 * \brief Doctor third scenario
*/

#include "thirdscenedoctor.h"

ThirdSceneDoctor::ThirdSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("HospitalLobbyBlurred.png").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape12-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(100, 500);
    addItem(character);

    money = new QGraphicsPixmapItem(QPixmap("Money.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    money->setPos(440, 285);
    addItem(money);

    moneyStack = new QGraphicsPixmapItem(QPixmap("MoneyStack.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    moneyStack->setPos(690, 285);
    addItem(moneyStack);

    //adding upper box to contain story
    box = new QGraphicsRectItem;
    box->setRect(40, 0, 1200, 80);
    box->setBrush(Qt::white);
    pen.setWidth(7);
    pen.setColor(Qt::black);
    box->setPen(pen);
    addItem(box);

    //setting text of story
    story = new QGraphicsTextItem("You Have Discovered by accident a medicine that cures a fatal disease on varss\nIt is up to you to price it.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    enter = new QGraphicsPixmapItem;

    enterState = 0;
}

void ThirdSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (enterState == 0)
            return;
        else if (enterState == 1)
            changeScene();
    }
}

void ThirdSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == money) {
        helping += 1;
        moneyGlobal += 1000;
        response = 0;
        QSound::play("ChaChing.wav");
        showResult();
    }
    else if (item == moneyStack) {
        moneyGlobal += 6000;
        response = 1;
        QSound::play("ChaChing.wav");
        showResult();
    }
}

void ThirdSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 3;
    QSound::play("ComputerSciFi.wav");
    clear();
}

void ThirdSceneDoctor::showResult() {
    removeItem(money);
    removeItem(moneyStack);
    box->setRect(490, 260, 300, 200);

    enter->setPixmap(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(740, 410);
    enter->setZValue(2);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0)
        story->setPlainText("You have decided to\nprice the medicine at\n100 Vollars.\nYour salary increased by\n 1000 Vollars.");
    else if (response == 1)
        story->setPlainText("You have decided to\nprice the medicine at\n600 Vollars.\nYour salary increased by\n 6000 Vollars.");

    enterState = 1;
}

void ThirdSceneDoctor::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == money) {
        money->setPixmap(QPixmap("MoneyGlow.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else if (item == moneyStack) {
        moneyStack->setPixmap(QPixmap("MoneyStackGlow.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else {
        money->setPixmap(QPixmap("Money.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        moneyStack->setPixmap(QPixmap("MoneyStack.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

