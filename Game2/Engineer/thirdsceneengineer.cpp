/**
 * \file thirdsceneengineer.cpp
 * \brief Third engineer scenario
*/

#include "thirdsceneengineer.h"

ThirdSceneEngineer::ThirdSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/ConferenceRoomCharacters.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape11-400.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

    //declaring graphics that will contain the options
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
    enter = new QGraphicsPixmapItem(QPixmap(":/images2/enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    //enterstate determines if we want to read the enter key, and what to do if we do
    //reponse is the state of the response the player chose
    enterState = 0;
    response = 0;

    //initializing sounds to be played later
    tick = new QSound(":/sounds/Tick.wav");
    ringtone = new QSound(":/sounds/Ringtone.wav");
    viber = new QSound(":/sounds/Vibration.wav");
}

/**
 * @brief ThirdSceneEngineer::keyPressEvent
 * @param event
 */
void ThirdSceneEngineer::keyPressEvent(QKeyEvent *event) {
    /**
     * Changes the text of the upper box\n
     * enterState sets result of pressing enter key.\n
     * If it is 0, pressing enter shows the options.\n
     * After showing the options, enterState is set to 1.\n
     * If enterState is 1, pressing enter key has no effect.\n
     * If enterState is 2, this means the scene is showing the result of the player's choice, and pressing enter switches back to main map.\n
    */
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        if (enterState == 0) {
            story->setPlainText("Your wife calls!\nWhat should you do?");
            removeItem(enter);
            setBackgroundBrush(QBrush(QImage(":/images2/ConferenceRoomBlurred.jpg").scaledToWidth(1280).scaledToHeight(720)));

            //adding phone
            phone = new QGraphicsPixmapItem(QPixmap(":/images2/PhoneIncoming.png").scaled(229, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

            //playing sounds
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

/**
 * @brief ThirdSceneEngineer::updateSeconds
 */
void ThirdSceneEngineer::updateSeconds() {
    /**
      * countSeconds counts the number of times this function has been called.\n
      * When countSeconds becomes negative, counter stops and displays the result.\n
      */
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

/**
 * @brief ThirdSceneEngineer::mousePressEvent
 * @param event
 */
void ThirdSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and results of option choosed is shown.\n
     */
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

/**
 * @brief ThirdSceneEngineer::changeScene
 */
void ThirdSceneEngineer::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 3;
    QSound::play(":/sounds/ComputerSciFi.wav");
    clear();
    deleteLater();
}

void ThirdSceneEngineer::rotatePhone() {
    if(phone->rotation() < 0)
        phone->setRotation(phone->rotation() + 14);
    else if(phone->rotation() > 0)
        phone->setRotation(phone->rotation() - 14);
}

/**
 * @brief ThirdSceneEngineer::showResult
 */
void ThirdSceneEngineer::showResult() {
    /**
     * Removes unwanted items.\n
     * Shows result depending on value of response.\n
     * enterState is set to 2 so that enter key is disabled after this\n
     */
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
