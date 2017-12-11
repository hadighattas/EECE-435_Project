#include "sixthscenedoctor.h"

SixthSceneDoctor::SixthSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("Vacation.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("DoctorVacation.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(530, 395);
    addItem(character);

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
    story = new QGraphicsTextItem("You are on vacation for one week with your family.\nThis is the only time off you get during the whole year.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    //enterstate determines if we want to read the enter key, and what to do if we do
    enterState = 0;
    response = 0;

    ringtone = new QSound("Ringtone.wav");
    viber = new QSound("Vibration.wav");

}

void SixthSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (enterState == 0) {
            story->setPlainText("Suddenly, an anoying patient starts calling.\nWhat should you choose?");
            removeItem(enter);

            //adding phone
            phone = new QGraphicsPixmapItem(QPixmap("PhonePatient.png").scaled(229, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            phone->setPos(60, 120);
            phone->setTransformationMode(Qt::SmoothTransformation);
            phone->setTransformOriginPoint(115, 250);
            phone->setRotation(-7);
            addItem(phone);
            ringtone->play();
            viber->play();

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(430, 225, 150, 80);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Answer his call.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(440, 250);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(680, 225, 150, 80);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Continue enjoying\n  your vaction.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(682, 240);
            addItem(option2Text);

            //timer seconds
            count = 8;
            timerPhone = new QTimer(this);
            connect(timerPhone, SIGNAL(timeout()), this, SLOT(rotatePhone()));
            timerPhone->start(1000);

            enterState = 1;
        }
        else if (enterState == 1) {
            ;
        }
        else if (enterState == 2) {
            changeScene();
        }
    }
}

void SixthSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        compliance += 1;
        response = 1;
        timerPhone->stop();
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        compliance -=1;
        response = 2;
        timerPhone->stop();
        showResult();
    }
}

void SixthSceneDoctor::showResult() {
    viber->stop();
    ringtone->stop();
    removeItem(phone);
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);

    box->setRect(490, 260, 300, 200);
    character->setPos(810, 340);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(500, 280);

    if (response == 0) {
        story->setPlainText("You chose to ignore\nthe call.\nMaybe it was something\nimportant...");
        compliance -= 1;
    }
    else if (response == 1) {
        story->setPlainText("You chose to answer.\nYou always put your\npatients first!");
    }
    else if (response == 2) {
        story->setPlainText("You chose to decline\nthe call.\nMaybe it was something\nimportant...");
    }

    enterState = 2;
}

void SixthSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 6;
    QSound::play("ComputerSciFi.wav");
    clear();
    deleteLater();
}

void SixthSceneDoctor::rotatePhone() {
    count--;
    if(phone->rotation() < 0)
            phone->setRotation(phone->rotation() + 14);
        else if(phone->rotation() > 0)
            phone->setRotation(phone->rotation() - 14);
    if(count == -1){
        timerPhone->stop();
        showResult();
        return ;
    }
}
