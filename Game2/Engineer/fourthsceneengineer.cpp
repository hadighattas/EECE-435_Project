/**
 * \file fourthsceneengineer.cpp
 * \brief Fourth engineer scenario
*/


#include "fourthsceneengineer.h"

FourthSceneEngineer::FourthSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("ConferenceRoomCharacters.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape11-400.png").scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(950, 350);
    addItem(character);

    vasa = new QGraphicsPixmapItem(QPixmap("VASA.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    vasa->setPos(1095, 150);
    addItem(vasa);

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
    story = new QGraphicsTextItem("During the meeting, your boss announces the new contract between VISCOVERY and VASA.\nYour company will help VASA build a space shuttle!");
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
}

/**
 * @brief FourthSceneEngineer::keyPressEvent
 * @param event
 */
void FourthSceneEngineer::keyPressEvent(QKeyEvent *event) {
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
            story->setPlainText("Your boss wants you to assume a managerial position in this project: either director or manager.\nWhat should you choose?");
            removeItem(enter);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(530, 465, 420, 80);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Director position: higher salaray but very little\ntime for your family.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(540, 480);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(530, 600, 420, 80);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Manager position: good but lower than director,\nlower salary but more time with family.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(540, 615);
            addItem(option2Text);

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
 * @brief FourthSceneEngineer::mousePressEvent
 * @param event
 */
void FourthSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and results of option choosed is shown.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        compliance += 1;
        family -= 1;
        response = 0;
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        compliance -= 1;
        family += 1;
        response = 1;
        showResult();
    }
}

/**
 * @brief FourthSceneEngineer::showResult
 */
void FourthSceneEngineer::showResult() {
    /**
     * Removes unwanted items.\n
     * Shows result depending on value of response.\n
     * enterState is set to 2 so that enter key is disabled after this\n
     * Updates moneyGlobal, which is global,depending on response.\n
     */
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);

    setBackgroundBrush(QBrush(QImage("ConferenceRoomBlurred.jpg").scaledToWidth(1280).scaledToHeight(720)));

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(500, 280);

    if (response == 0) {
        story->setPlainText("You chose the director\nposition. Your salary will\nincrease by 5000 Vollars.\nIn the next 4 months, \nyou will barely see\nyour family.");
        moneyGlobal += 5000;
    }
    else if (response == 1) {
        story->setPlainText("You chose the manager\nposition. Your salary will\nincrease by 2000 Vollars.\nYour family is glad you \nstill have time to\nsee them.");
        moneyGlobal += 2000;
    }

    enterState = 2;
}

/**
 * @brief FourthSceneEngineer::changeScene
 */
void FourthSceneEngineer::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 4;
    QSound::play("ComputerSciFi.wav");
    clear();
}
