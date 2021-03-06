/**
 * \file secondsceneengineer.cpp
 * \brief Second engineer scenario
*/

#include "secondsceneengineer.h"

SecondSceneEngineer::SecondSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/BreakRoom.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    addAliens();

    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape11-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(200, 250);
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
    option3 = new QGraphicsRectItem;
    option3Text = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("It's 10AM, and you're talking to your colleagues in the lobby during the coffee break.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap(":/images2/enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    enterState = 0;
}

/**
 * @brief SecondSceneEngineer::addAliens
 */
void SecondSceneEngineer::addAliens() {
    /**
     * Creates 3 aliens randomly at specific positions.
     */
    RandomAlien *alien1 = new RandomAlien;
    alien1->setPixmap(alien1->pixmap().scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien1->setPos(210, 500);
    addItem(alien1);

    RandomAlien *alien2 = new RandomAlien;
    alien2->setPixmap(alien2->pixmap().scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien2->setPos(820, 160);
    addItem(alien2);

    RandomAlien *alien3 = new RandomAlien;
    alien3->setPixmap(alien3->pixmap().scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    alien3->setPos(1020, 220);
    addItem(alien3);
}

/**
 * @brief SecondSceneEngineer::keyPressEvent
 * @param event
 */
void SecondSceneEngineer::keyPressEvent(QKeyEvent *event) {
    /**
     * Changes the text of the upper box\n
     * enterState sets result of pressing enter key.\n
     * If it is 0, pressing enter shows the options.\n
     * After showing the options, enterState is set to 1.\n
     * If enterState is 1, pressing enter key has no effect.\n
    */
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            box->setRect(40, 0, 1200, 100);
            story->setPlainText("Suddenly, your co-worker accidentally spills his coffee in you.\n You have an important meeting with your boss in 20 min!\nWhat should you do?");
            removeItem(enter);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(390, 330, 500, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Ask him to buy you new pants right now.");
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
            option2Text->setPlainText("Recognize it was an accident and let it go.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(400, 420);
            addItem(option2Text);

            //adding third option
            option3->setBrush(Qt::white);
            option3->setPen(pen);
            option3->setRect(390, 490, 500, 40);
            addItem(option3);

            //setting text of third option
            option3Text->setPlainText("Report him to the HR department.");
            option3Text->setDefaultTextColor(QColor(Qt::black));
            option3Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option3Text->setPos(400, 500);
            addItem(option3Text);

            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
}

/**
 * @brief SecondSceneEngineer::mousePressEvent
 * @param event
 */
void SecondSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and scene is switched back to the main map.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        forgivingness -= 1;
        changeScene();
    }
    else if (item == option2 || item == option2Text) {
        forgivingness += 1;
        changeScene();
    }
    else if (item == option3 || item == option3Text) {
        forgivingness -= 1;
        changeScene();
    }
}

/**
 * @brief SecondSceneEngineer::changeScene
 */
void SecondSceneEngineer::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 2;
    QSound::play(":/sounds/ComputerSciFi.wav");
    clear();
    deleteLater();
}
