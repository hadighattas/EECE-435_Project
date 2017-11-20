#include "firstscenedoctor.h"

FirstSceneDoctor::FirstSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("Lobby.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    addAliens();

    character = new QGraphicsPixmapItem(QPixmap("Shape12-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(928, 250);
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
    option3 = new QGraphicsRectItem;
    option3Text = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("Welcome to VOPITAL, the best hospital on Varss!\n It's 8AM and you just arrived to work.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    enterState = 0;
}

void FirstSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            box->setRect(40, 0, 1200, 100);
            story->setPlainText("Your first patient today is a very poor citizen of VArss.\nThe hospital direction asks if you would be willing to diagnose him without being paid.\nWhat should you do?");
            removeItem(enter);

            RandomAlien *alien = new RandomAlien;
            alien->setPixmap(alien->pixmap().scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            alien->setPos(800, 250);
            addItem(alien);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(440, 315, 320, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Help him out and don't ask for money.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(450, 325);
            addItem(option1Text);

            //adding second optio
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(440, 395, 320, 40);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Refuse to help him out.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(450, 405);
            addItem(option2Text);

            //adding third option
            option3->setBrush(Qt::white);
            option3->setPen(pen);
            option3->setRect(440, 475, 320, 40);
            addItem(option3);

            //setting text of third option
            option3Text->setPlainText("Help him out and ask to be paid later.");
            option3Text->setDefaultTextColor(QColor(Qt::black));
            option3Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option3Text->setPos(450, 485);
            addItem(option3Text);

            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
}

void FirstSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        doctorValues << "HELPING OTHERS" << "HELPING OTHERS";
        changeScene();
    }
    else if (item == option2 || item == option2Text) {
        if (doctorValues.contains("HELPING OTHERS"))
                doctorValues.removeOne("HELPING OTHERS");
        changeScene();
    }
    else if (item == option3 || item == option3Text) {
        doctorValues << "HELPING OTHERS";
        changeScene();
    }
}

void FirstSceneDoctor::addAliens() {
    RandomAlien *alien1 = new RandomAlien;
    alien1->setPixmap(alien1->pixmap().scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien1->setPos(190, 340);
    addItem(alien1);

    RandomAlien *alien2 = new RandomAlien;
    alien2->setPixmap(alien2->pixmap().scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien2->setPos(800, 160);
    addItem(alien2);

    RandomAlien *alien3 = new RandomAlien;
    alien3->setPixmap(alien3->pixmap().scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien3->setPos(1050, 545);
    addItem(alien3);
}

void FirstSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 1;
    QSound::play("ComputerSciFi.wav");
    clear();
    delete this;
}