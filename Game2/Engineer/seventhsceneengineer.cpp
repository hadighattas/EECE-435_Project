/**
 * \file seventhsceneengineer.cpp
 * \brief Seventh engineer scenario
*/

#include "seventhsceneengineer.h"

SeventhSceneEngineer::SeventhSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("Lobby.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape11-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(928, 250);
    addItem(character);

    blindCharacter = new QGraphicsPixmapItem(QPixmap("Blind.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    blindCharacter->setPos(245, 170);
    addItem(blindCharacter);

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
    fire = new QGraphicsPixmapItem;

    timePassedTimer = new QTimer;
    connect(timePassedTimer, SIGNAL(timeout()), this, SLOT(updateScene()));

    //setting text of story
    story = new QGraphicsTextItem("There's a fire in the building!\nEveryone has already left the building, when suddenly...");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    enterState = 0;
    response = 0;
    timePassed = 0;

    fireAlarm = new QSound("FireAlarm.wav");
    fireSound = new QSound("FireSound.wav");
}

/**
 * @brief SeventhSceneEngineer::keyPressEvent
 * @param event
 */
void SeventhSceneEngineer::keyPressEvent(QKeyEvent *event) {
    /**
     * Changes the text of the upper box\n
     * enterState sets result of pressing enter key.\n
     * If it is 0, pressing enter shows the options.\n
     * After showing the options, enterState is set to 1.\n
     * If enterState is 1, pressing enter key has no effect.\n
     * If enterState is 2, this means the scene is showing the result of the player's choice, and pressing enter switches back to main map.\n
    */
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            box->setRect(40, 0, 1200, 100);
            story->setPlainText("You notice your blind colleague can't find his way out!\nYou don't have much time to decide.\nWhat shoudl you do?");
            removeItem(enter);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(440, 500, 500, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Leave and don't look back.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(450, 510);
            addItem(option1Text);

            //adding second optio
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(440, 560, 500, 40);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Save him at the risk of losing your own life.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(450, 570);
            addItem(option2Text);

            enterState = 1;

            fire->setPixmap(QPixmap("Fire.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            fire->setPos(425, 200);
            addItem(fire);

            timePassedTimer->start(500);

            fireAlarm->play();
            fireSound->play();
        }
    }
    else if (enterState == 1)
        return;
    else if (enterState == 2)
        changeScene();
}

/**
 * @brief SeventhSceneEngineer::mousePressEvent
 * @param event
 */
void SeventhSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and results of option choosed is shown.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        courage -= 1;
        helping -= 1;
        response = 1;
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        courage += 1;
        helping += 1;
        response = 2;
        showResult();
    }
}

/**
 * @brief SeventhSceneEngineer::changeScene
 */
void SeventhSceneEngineer::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 7;
    QSound::play("ComputerSciFi.wav");
    clear();
    deleteLater();
}

/**
 * @brief SeventhSceneEngineer::showResult
 */
void SeventhSceneEngineer::showResult() {
    /**
     * Removes unwanted items.\n
     * Shows result depending on value of response.\n
     * enterState is set to 2 so that enter key is disabled after this\n
     */
    timePassedTimer->stop();
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);
    removeItem(fire);
    fireAlarm->stop();
    fireSound->stop();

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0) {
        courage -= 1;
        helping -= 1;

        story->setPlainText("You took too much time to\ndecide, and now your\ncolleague is dead.\nThis was a tough decision.");
        removeItem(blindCharacter);
    }
    else if (response == 1) {
        story->setPlainText("You got out safely just in\ntime, but your colleague\nperished in the flames.");
        removeItem(blindCharacter);
    }
    else if (response == 2) {
        story->setPlainText("Congratulations!\nYou saved yourself and\nyour colleague.\nEveryone now thinks of\nyou as a hero!");
        blindCharacter->setPos(950, 400);
        blindCharacter->setPixmap(QPixmap("Blind.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    enterState = 2;
}

/**
 * @brief SeventhSceneEngineer::updateScene
 */
void SeventhSceneEngineer::updateScene() {
    /**
     * Function called every second.\n
     * Updates size of fire image by scaling it.\n
     * After time has passed, scene is switched to show the result.\n
     */
    timePassed++;
    QPixmap oldPixmap = fire->pixmap();
    fire->setPixmap(QPixmap("Fire.png").scaled(oldPixmap.width() + 12, oldPixmap.height() + 12, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    fire->setPos(fire->x(), fire->y() - 5);
    if (timePassed == 15) {
        showResult();
    }
}
