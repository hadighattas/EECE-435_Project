/**
 * \file eightsceneengineer.cpp
 * \brief Eight engineer scenario
*/

#include "eigthsceneengineer.h"

EigthSceneEngineer::EigthSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("CubiclesEmpty.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape11-400.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(980, 450);
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
    story = new QGraphicsTextItem("Time to be excited!\nThe new rocket you've been developing in collaboration with vasa is scheduled to launch tomorrow at 8AM sharp.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1190, 35);
    addItem(enter);

    //enterstate determines if we want to read the enter key, and what to do if we do
    enterState = 0;

    //declare sound
    rocket = new QSound("Rocket.wav");
}

/**
 * @brief EigthSceneEngineer::keyPressEvent
 * @param event
 */
void EigthSceneEngineer::keyPressEvent(QKeyEvent *event) {
    /**
     * Changes the text of the upper box\n
     * enterState sets result of pressing enter key.\n
     * If it is 0, pressing enter shows the options.\n
     * After showing the options, enterState is set to 1.\n
     * If enterState is 1, pressing enter key has no effect.\n
     * If enterState is 2, this means the scene is showing the result of the player's choice, and pressing enter switches back to main map.\n
     * In this case we also have to stop the sound of the rocket\n
    */
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            box->setRect(40, 0, 1200, 100);
            story->setPlainText("You are reviewing the final documents, when you realize one of the shuttle's' components has not been tested\n under extreme conditions.\nYou know this may lead to catastrophic consequences. What should you do?");
            removeItem(enter);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(200, 280, 500, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Reschedule the launch at the cost of losing a lot of money.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(210, 290);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(200, 340, 200, 40);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("??????????????????????????.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(210, 350);
            addItem(option2Text);

            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
    else if (enterState == 2) {
        rocket->stop();
        changeScene();
    }
}

/**
 * @brief EigthSceneEngineer::mousePressEvent
 * @param event
 */
void EigthSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and results of option choosed is shown.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        honesty += 1;
        response = 0;
        moneyGlobal -= 5000;
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        honesty -= 1;
        response = 1;
        showResult();
    }
}

/**
 * @brief EigthSceneEngineer::changeScene
 */
void EigthSceneEngineer::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 8;
    QSound::play("ComputerSciFi.wav");
    clear();
}

/**
 * @brief EigthSceneEngineer::showResult
 */
void EigthSceneEngineer::showResult() {
    /**
     * Removes unwanted items.\n
     * Shows result depending on value of response.\n
     * enterState is set to 2 so that enter key is disabled after this\n
     */
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);

    setBackgroundBrush(QBrush(QImage("SpaceShuttle.png").scaledToWidth(1280).scaledToHeight(720)));

    vasa = new QGraphicsPixmapItem(QPixmap("VASA.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    vasa->setPos(1095, 150);
    addItem(vasa);

    rocket->play();

    enter->setPos(1150, 35);
    removeItem(character);
    addItem(enter);

    if (response == 0)
        story->setPlainText("The space shuttle is finally ready to take off!\nYou have the privilege of being one of its first passangers.\nEnjoy the ride :)");
    else if (response == 1)
        story->setPlainText("");

    enterState = 2;
}
