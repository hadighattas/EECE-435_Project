#include "secondscenedoctor.h"

SecondSceneDoctor::SecondSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("HospitalLobby.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape12-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(470, 400);
    addItem(character);

    your_brother = new QGraphicsPixmapItem(QPixmap("Brother.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    your_brother->setPos(830, 360);
    addItem(your_brother);

    stranger = new QGraphicsPixmapItem(QPixmap("Stranger.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    stranger->setPos(1000, 450);
    addItem(stranger);

    //adding upper box to contain story
    box = new QGraphicsRectItem;
    box->setRect(40, 0, 1200, 80);
    box->setBrush(Qt::white);
    pen.setWidth(7);
    pen.setColor(Qt::black);
    box->setPen(pen);
    addItem(box);

    option1 = new QGraphicsRectItem;
    option1Text = new QGraphicsTextItem;
    option2 = new QGraphicsRectItem;
    option2Text = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("After a long day at work, you are informed that two badly injured patients are on their way.\nAs soon as they arrive, you realize that...");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    clickState = 0;
    enterState = 0;
}

void SecondSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            story->setPlainText("One of them is your brother, and the other one is a stranger whose condition is more critical.\nWho do you choose to help?");
            removeItem(enter);

            pen.setWidth(5);


            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(860, 300, 120, 50);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Brother");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
            option1Text->setPos(875, 310);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(1025, 385, 120, 50);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Stranger");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
            option2Text->setPos(1030, 395);
            addItem(option2Text);

            //permission to click on brother or stranger
            clickState = 1;
            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
    else if (enterState == 2)
        changeScene();
}

void SecondSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (clickState == 0)
        return;
    else if (clickState == 1) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item == your_brother) {
            family += 1;
            response = 0;
            showResult();
        }
        else if (item == stranger) {
            family -= 1;
            compliance += 1;
            response = 1;
            showResult();
        }
    }
}

void SecondSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 2;
    QSound::play("ComputerSciFi.wav");
    clear();
}

void SecondSceneDoctor::showResult() {
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0) {
        story->setPlainText("You have decided to\nsave your brother.\nthe kind stranger is\ndead.");
        removeItem(stranger);
        character->setPos(1000, 450);
    }
    else if (response == 1) {
        story->setPlainText("You have decided to\nsave the stranger.\nYour brother is okay.");
        removeItem(your_brother);
        character->setPos(810, 340);
    }
    enterState = 2;
}

void SecondSceneDoctor::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (clickState == 0)
        return;
    else if (clickState == 1) {
         QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
         if (item == your_brother) {
             your_brother->setPixmap(QPixmap("BrotherGlow.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         }
         else if (item == stranger) {
             stranger->setPixmap(QPixmap("StrangerGlow.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         }
         else {
             your_brother->setPixmap(QPixmap("Brother.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
             stranger->setPixmap(QPixmap("Stranger.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         }
    }
}

