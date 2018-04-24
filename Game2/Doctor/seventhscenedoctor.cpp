/**
 * \file seventhscenedoctor.cpp
 * \brief Seventh doctor scenario
*/

#include "seventhscenedoctor.h"

SeventhSceneDoctor::SeventhSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/OperationRoom2.png").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape12-400.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(700, 400);
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
    story = new QGraphicsTextItem("You are in the operating room, getting ready for the next patient who's coming.\nSuddenly...");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    option1 = new QGraphicsRectItem;
    option1->setBrush(Qt::white);
    option1->setPen(pen);
    option1->setRect(480, 230, 340, 40);

    option1Text = new QGraphicsTextItem;
    option1Text->setPlainText("Try to fix the object.");
    option1Text->setDefaultTextColor(QColor(Qt::black));
    option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
    option1Text->setPos(490, 240);

    option2 = new QGraphicsRectItem;
    option2->setBrush(Qt::white);
    option2->setPen(pen);
    option2->setRect(480, 290, 340, 40);

    option2Text = new QGraphicsTextItem;
    option2Text->setPlainText("Hide it and don't tell anyone.");
    option2Text->setDefaultTextColor(QColor(Qt::black));
    option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
    option2Text->setPos(490, 300);

    option3 = new QGraphicsRectItem;
    option3->setBrush(Qt::white);
    option3->setPen(pen);
    option3->setRect(480, 360, 340, 40);

    option3Text = new QGraphicsTextItem;
    option3Text->setPlainText("Tell the truth.");
    option3Text->setDefaultTextColor(QColor(Qt::black));
    option3Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
    option3Text->setPos(490, 370);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap(":/images2/enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    breakingSound = new QSound(":/sounds/BreakingSound.wav");

    clickState = 0;
    enterState = 0;
}

/**
 * @brief SeventhSceneDoctor::keyPressEvent
 * @param event
 */
void SeventhSceneDoctor::keyPressEvent(QKeyEvent *event) {
    /**
     * Changes the text of the upper box\n
     * enterState sets result of pressing enter key.\n
     * If it is 0, pressing enter shows the options.\n
     * After showing the options, enterState is set to 1.\n
     * If enterState is 1, pressing enter key has no effect.\n
     * clickState is set to 1 to allow player to click on an option in first scenario.\n
     * If enterState is 2, pressing enter shows options in second scenario.\n
     * If enterState is 3, pressing enter has no effect.\n
    */
    if (enterState == 0) { //state 0 is when the user has never pressed enter
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            breakingSound->play();
            story->setPlainText("You accidentally break an object in the room.\nWhat should you do?");
            setBackgroundBrush(QBrush(QImage(":/images2/OperationRoomObject.png").scaledToWidth(1280).scaledToHeight(720)));
            removeItem(enter);

            pen.setWidth(5);

            //adding first option
            addItem(option1);

            //setting text of first option
            addItem(option1Text);

            //adding second option
            addItem(option2);

            //setting text of second option
            addItem(option2Text);

            //adding third option
            addItem(option3);

            //setting text of third option
            addItem(option3Text);


            //permission to click
            clickState = 1; // clicking on option of first situation
            enterState = 1;
        }
    }
    else if (enterState == 1) // user has pressed enter and has to click on option
        return;
    else if (enterState == 2) { // user has chosen option and now we start another situation with nursw
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            breakingSound->play();
            story->setPlainText("The nurse accidentally breaks one of your tools.\nWhat should you do?");
            setBackgroundBrush(QBrush(QImage(":/images2/OperationRoomObject.png").scaledToWidth(1280).scaledToHeight(720)));
            removeItem(enter);

            pen.setWidth(5);

            //adding first option
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Report her to the HR department.");
            addItem(option1Text);

            //adding second option

            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Ask her to buy you a new tool.");
            addItem(option2Text);

            //adding third option

            addItem(option3);

            //setting text of third option
            option3Text->setPlainText("Recognize it was an error and let it go.");
            addItem(option3Text);


            //permission to click
            clickState = 2;
            enterState = 3;
        }
    }
    else if (enterState == 3) { // user has pressed enter for the scene with nurse and options are shown
        return;
    }
}

/**
 * @brief SeventhSceneDoctor::mousePressEvent
 * @param event
 */
void SeventhSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * Before clickState is set to 1, clicking on screen has no effect.\n
     * If player clicks on one option, values are updated and scene is switched to second scenario.\n
     * If clickState is 2, player can click on option of second scenario.\n
     * After this, values are updated and scene is switched back to main map.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (clickState == 1) {
        if (item == option1 || item == option1Text) {
            honesty -= 1;
            secondScenario();
        }
        else if (item == option2 || item == option2Text) {
            honesty -= 2;
            secondScenario();
        }
        else if (item == option3 || item == option3Text) {
            honesty += 1;
            secondScenario();
        }
    }
    else if (clickState == 2) {
        if (item == option1 || item == option1Text) {
            forgivingness -= 2;
            changeScene();
        }
        else if (item == option2 || item == option2Text) {
            forgivingness -= 1;
            changeScene();
        }
        else if (item == option3 || item == option3Text) {
            forgivingness += 1;
            changeScene();
        }
    }
}

/**
 * @brief SeventhSceneDoctor::secondScenario
 */
void SeventhSceneDoctor::secondScenario() {
    /**
     * Removes unwanted items.\n
     * Adds graphics for second scenario.\n
     * enterState is set to 2 so that enter key shows options of second scenario.\n
     */
    setBackgroundBrush(QBrush(QImage(":/images2/OperationRoom2.png").scaledToWidth(1280).scaledToHeight(720)));

    character->setPos(250, 400);
    addItem(enter);
    removeItem(option1);
    removeItem(option2);
    removeItem(option3);
    removeItem(option1Text);
    removeItem(option2Text);
    removeItem(option3Text);

    nurse = new QGraphicsPixmapItem(QPixmap(":/images2/Nurse.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    nurse->setPos(700, 400);
    addItem(nurse);

    story->setPlainText("Now suppose you are getting ready for an operation, and a nurse is helping you.\nWhen suddenly...");

    clickState = 2;
    enterState = 2;
}

/**
 * @brief SeventhSceneDoctor::changeScene
 */
void SeventhSceneDoctor::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 8;
    QSound::play(":/sounds/ComputerSciFi.wav");
    clear();
    deleteLater();
}
