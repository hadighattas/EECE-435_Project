#include "thirdsceneengineer.h"

ThirdSceneEngineer::ThirdSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("ConferenceRoomCharacters.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape11-400.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

    option1 = new QGraphicsRectItem;
    option1Text = new QGraphicsTextItem;
    option2 = new QGraphicsRectItem;
    option2Text = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("20 min later, you are in the conference room for an important meeting.\nYour boss is talking when suddenly...");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    //enterstate determines if we want to read the enter key, and what to do if we do
    //reponse is the state of the response the player chose
    enterState = 0;
    response = 0;

    tick = new QSound("Tick.wav");
    ringtone = new QSound("Ringtone.wav");
    viber = new QSound("Vibration.wav");
}

void ThirdSceneEngineer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (enterState == 0) {
            story->setPlainText("Your wife calls!\nWhat should you do?");
            removeItem(enter);
            setBackgroundBrush(QBrush(QImage("ConferenceRoomBlurred.jpg").scaledToWidth(1280).scaledToHeight(720)));

            //adding phone
            phone = new QGraphicsPixmapItem(QPixmap("PhoneIncoming.png").scaled(229, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            phone->setPos(60, 120);
            phone->setTransformationMode(Qt::SmoothTransformation);
            phone->setTransformOriginPoint(115, 250);
            phone->setRotation(-7);
            addItem(phone);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(390, 330, 500, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Answer the call: it might be important!");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(400, 340);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(390, 410, 500, 40);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Ignore the call out of respect for your boss.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(400, 420);
            addItem(option2Text);

            ringtone->play();
            viber->play();

            //timer seconds
            countSeconds = 8;
            secondsLeft = new QTimer(this);
            connect(secondsLeft, SIGNAL(timeout()), this, SLOT(updateSeconds()));
            secondsLeft->start(1000);

            secondsLeftText = new QGraphicsTextItem(QString::number(countSeconds));
            secondsLeftText->setDefaultTextColor(QColor(Qt::black));
            secondsLeftText->setFont(QFont("Digital-7", 100, QFont::Normal, false));
            secondsLeftText->setPos(1000, 150);
            addItem(secondsLeftText);

            sec = new QGraphicsTextItem("sec");
            sec->setDefaultTextColor(QColor(Qt::black));
            sec->setFont(QFont("Digital-7", 80, QFont::Normal, false));
            sec->setPos(1070, 170);
            addItem(sec);

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

void ThirdSceneEngineer::updateSeconds() {
    countSeconds--;
    rotatePhone();
    if(countSeconds == -1){
        secondsLeft->stop();
        showResult();
        return ;
    }
    else if(countSeconds == 3){
        secondsLeftText->setDefaultTextColor(QColor(Qt::red));
        sec->setDefaultTextColor(QColor(Qt::red));
    }
    tick->play();
    secondsLeftText->setPlainText(QString::number(countSeconds));
}

void ThirdSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        family += 1;
        compliance -= 1;
        response = 1;
        secondsLeft->stop();
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        compliance += 1;
        family -= 1;
        response = 2;
        secondsLeft->stop();
        showResult();
    }
}

void ThirdSceneEngineer::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 3;
    QSound::play("ComputerSciFi.wav");
    clear();
}

void ThirdSceneEngineer::rotatePhone() {
    if(phone->rotation() < 0)
        phone->setRotation(phone->rotation() + 14);
    else if(phone->rotation() > 0)
        phone->setRotation(phone->rotation() - 14);
}

void ThirdSceneEngineer::showResult() {
    removeItem(phone);
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);
    removeItem(secondsLeftText);
    removeItem(sec);
    tick->stop();
    ringtone->stop();
    viber->stop();

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0) {
        story->setPlainText("Your wife sent you \na message and she's pissed\nbecause you didn't answer!\nYou also annoyed everybody\nat the meeting because\nyour phone rang for\ntoo long.");
        family -= 1;
        compliance -= 1;
    }
    else if (response == 1)
        story->setPlainText("You took a call during a \nmeeting.\nYour boss is now pissed!");
    else if (response == 2)
        story->setPlainText("You hung up on your wife.\nBe sure to call her later!");

    enterState = 2;
}
