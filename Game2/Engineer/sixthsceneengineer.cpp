/**
 * \file sixthsceneengineer.cpp
 * \brief Sixth engineer scenario
*/

#include "sixthsceneengineer.h"

SixthSceneEngineer::SixthSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("Cubicles.jpg").scaledToWidth(1280).scaledToHeight(720)));
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
    option3 = new QGraphicsRectItem;
    option3Text = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("You are circulating between the cubicles, checking on your team's work.\n");
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

    notification = new QSound("Notification.wav");
}

/**
 * @brief SixthSceneEngineer::keyPressEvent
 * @param event
 */
void SixthSceneEngineer::keyPressEvent(QKeyEvent *event) {
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
            setBackgroundBrush(QBrush(QImage("CubiclesBlurred.jpg").scaledToWidth(1280).scaledToHeight(720)));
            box->setRect(40, 0, 1200, 100);
            story->setPlainText("Suddenly you receive this notification on your phone.\nYou know the money does not belong to you and was transferred by error.\nWhat should you do?");
            removeItem(enter);

            notification->play();

            //adding phone
            phone = new QGraphicsPixmapItem(QPixmap("MessagePhone.png").scaled(230, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            phone->setPos(60, 120);
            addItem(phone);

            pen.setWidth(5);

            //adding first option
            option1->setBrush(Qt::white);
            option1->setPen(pen);
            option1->setRect(480, 280, 300, 40);
            addItem(option1);

            //setting text of first option
            option1Text->setPlainText("Call the bank and report the error.");
            option1Text->setDefaultTextColor(QColor(Qt::black));
            option1Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option1Text->setPos(490, 290);
            addItem(option1Text);

            //adding second option
            option2->setBrush(Qt::white);
            option2->setPen(pen);
            option2->setRect(480, 340, 300, 40);
            addItem(option2);

            //setting text of second option
            option2Text->setPlainText("Keep the money to yourself.");
            option2Text->setDefaultTextColor(QColor(Qt::black));
            option2Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option2Text->setPos(490, 350);
            addItem(option2Text);

            //adding third option
            option3->setBrush(Qt::white);
            option3->setPen(pen);
            option3->setRect(480, 410, 300, 40);
            addItem(option3);

            //setting text of third option
            option3Text->setPlainText("Give the money to charity.");
            option3Text->setDefaultTextColor(QColor(Qt::black));
            option3Text->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
            option3Text->setPos(490, 420);
            addItem(option3Text);

            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
    else if (enterState == 2)
        changeScene();
}

/**
 * @brief SixthSceneEngineer::mousePressEvent
 * @param event
 */
void SixthSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    /**
     * If player clicks on one option, values are updated and results of option choosed is shown.\n
     */
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == option1 || item == option1Text) {
        honesty += 1;
        response = 0;
        showResult();
    }
    else if (item == option2 || item == option2Text) {
        honesty -= 1;
        response = 1;
        showResult();
    }
    else if (item == option3 || item == option3Text) {
        helping += 1;
        honesty -= 1;
        response = 2;
        showResult();
    }
}

/**
 * @brief SixthSceneEngineer::changeScene
 */
void SixthSceneEngineer::changeScene() {
    /**
     * Gets the view that is showing the current scene.\n
     * Sets back the scene to the parent of the current scene, which is the main map.\n
     */
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 6;
    QSound::play("ComputerSciFi.wav");
    clear();
    deleteLater();
}

/**
 * @brief SixthSceneEngineer::showResult
 */
void SixthSceneEngineer::showResult() {
    /**
     * Removes unwanted items.\n
     * Shows result depending on value of response.\n
     * enterState is set to 2 so that enter key is disabled after this\n
     * Updates moneyGlobal, which is global,depending on response.\n
     */
    removeItem(phone);
    removeItem(option1);
    removeItem(option1Text);
    removeItem(option2);
    removeItem(option2Text);
    removeItem(option3);
    removeItem(option3Text);

    box->setRect(490, 260, 300, 200);

    enter->setPos(740, 410);
    addItem(enter);

    story->setPos(495, 280);

    if (response == 0) {
        story->setPlainText("You did the right thing!\nThe bank rewards you by\ngiving you 100 vollars.");
        moneyGlobal += 100;
    }
    else if (response == 1) {
        story->setPlainText("You now have more money,\nbut this was surely not\nthe right thing to do.");
        moneyGlobal += 500;
    }
    else if (response == 2)
        story->setPlainText("It's nice that you thought\nof helping others.\nBut this money wasn't\nyours to give away.");

    enterState = 2;
}
