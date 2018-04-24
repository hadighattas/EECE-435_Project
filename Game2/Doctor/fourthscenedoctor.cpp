#include "fourthscenedoctor.h"

FourthSceneDoctor::FourthSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/HospitalOffice.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape12-400.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(950, 350);
    addItem(character);

    //adding upper box to contain story
    box = new QGraphicsRectItem;
    box->setRect(40, 0, 1200, 80);
    box->setBrush(Qt::white);
    pen.setWidth(7);
    pen.setColor(Qt::black);
    box->setPen(pen);
    addItem(box);

    //setting text of story
    story = new QGraphicsTextItem("A water pump has failed in the hospital, leading to a major flood in your office.\nJust before going out, you have time to choose only one of these items...");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    briefcase = new QGraphicsPixmapItem;
    records = new QGraphicsPixmapItem;
    water = new QGraphicsPixmapItem;
    waterSound = new QSound(":/sounds/Water.wav");
    waterSound->setLoops(2);

    countTimer = 30;
    waterTimer = new QTimer(this);
    connect(waterTimer, SIGNAL(timeout()), this, SLOT(updateScene()));

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap(":/images2/enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    //enterstate determines if we want to read the enter key, and what to do if we do
    //reponse is the state of the response the player chose
    enterState = 0;
    response = 0;
}

void FourthSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (enterState == 0) {
            story->setPlainText("All the medical records of your patients, or a suitcase containing 5,000 Vollars.\nWhich one should you choose?");
            removeItem(enter);

            pen.setWidth(5);

            records->setPixmap(QPixmap(":/images2/Records.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            records->setPos(440, 285);
            addItem(records);

            briefcase->setPixmap(QPixmap(":/images2/Briefcase.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            briefcase->setPos(690, 285);
            addItem(briefcase);

            enterState = 1;

            water->setPixmap(QPixmap(":/images2/Water.png").scaled(1279, 576, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            water->setPos(0, 660);
            waterTimer->start(250);
            waterSound->play();
            addItem(water);
        }
        else if (enterState == 1) {
            ;
        }
        else if (enterState == 2) {
            changeScene();
        }
    }
}

void FourthSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == records) {
        compliance += 1;
        response = 1;
        showResult();
    }
    else if (item == briefcase) {
        compliance -= 1;
        response = 2;
        showResult();
    }
}

void FourthSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 4;
    QSound::play(":/sounds/ComputerSciFi.wav");
    clear();
    deleteLater();
}

void FourthSceneDoctor::showResult() {
    waterTimer->stop();
    waterSound->stop();
    removeItem(records);
    removeItem(briefcase);
    removeItem(water);

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0) {
        story->setPlainText("You took too much time to\nmake a decision. You\nlost both items.");
        compliance -= 1;
    }
    else if (response == 1)
        story->setPlainText("You chose to save the\nrecords.\nYou always put your\npatients first!");
    else if (response == 2) {
        story->setPlainText("You chose to save the money.\nYour salary will increase by\n5000 vollars.");
        moneyGlobal += 5000;
    }
    enterState = 2;
}

void FourthSceneDoctor::updateScene(){
    countTimer--;
    water->setPos(water->x(), water->y() - 13);
    if (countTimer == 0) {
        showResult();
    }
}
