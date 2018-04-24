#include "fifthscenedoctor.h"

FifthSceneDoctor::FifthSceneDoctor(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage(":/images2/OperationRoomDark.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap(":/images2/Shape12-400.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(700, 400);
    addItem(character);

    //declare medicine and exit
    medicine = new QGraphicsPixmapItem;
    exit = new QGraphicsPixmapItem;

    //adding upper box to contain story
    box = new QGraphicsRectItem;
    box->setRect(40, 0, 1200, 80);
    box->setBrush(Qt::white);
    pen.setWidth(7);
    pen.setColor(Qt::black);
    box->setPen(pen);
    addItem(box);

    //setting text of story
    story = new QGraphicsTextItem("Your wife is sick and needs a medicine that is out of stock everywhere on varss.\nYou know the hospital keeps a small stock of it for emergency cases.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap(":/images2/enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);

    footsteps = new QSound(":/sounds/Footsteps.wav");
    footsteps->setLoops(2);

    response = 0;
    clickState = 0;
    enterState = 0;

    //initialize timer
    countTime = 12;
    timeLeft = new QTimer(this);
    connect(timeLeft, SIGNAL(timeout()), this, SLOT(updateScene()));
}

void FifthSceneDoctor::keyPressEvent(QKeyEvent *event) {
    if (enterState == 0) {
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            timeLeft->start(1000);

            timeLeftText = new QGraphicsTextItem(QString::number(countTime));
            timeLeftText->setDefaultTextColor(QColor(Qt::white));
            timeLeftText->setFont(QFont("Digital-7", 100, QFont::Normal, false));
            timeLeftText->setPos(980, 150);
            addItem(timeLeftText);

            sec = new QGraphicsTextItem("sec");
            sec->setDefaultTextColor(QColor(Qt::white));
            sec->setFont(QFont("Digital-7", 80, QFont::Normal, false));
            sec->setPos(1070, 170);
            addItem(sec);

            story->setPlainText("Should you steal it, knowing the hospital wouldn't let you take it\nor should you just leave?\nQuick! Someone's coming.");
            box->setRect(40, 0, 1200, 100);

            removeItem(enter);
            footsteps->play();

            pen.setWidth(5);

            medicine->setPixmap(QPixmap(":/images2/Medicine.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            medicine->setPos(300, 460);
            addItem(medicine);

            exit->setPixmap(QPixmap(":/images2/Exit.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            exit->setPos(1070, 570);
            addItem(exit);

            //permission to click on brother or stranger
            clickState = 1;
            enterState = 1;
        }
    }
    else if (enterState == 1)
        return;
    else if (enterState == 2)
        changeScene();
}

void FifthSceneDoctor::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (clickState == 0)
        return;
    else if (clickState == 1) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item == medicine) {
            family += 1;
            compliance -= 1;
            response = 1;
            clickState = 2;
            timeLeft->stop();
            showResult();
        }
        else if (item == exit) {
            family -= 1;
            compliance += 1;
            response = 2;
            clickState = 2;
            timeLeft->stop();
            showResult();
        }
    }
}

void FifthSceneDoctor::updateScene() {
    countTime--;
    if(countTime == -1){
        timeLeft->stop();
        clickState = 2;
        showResult();
        return ;
    }
    else if(countTime == 3) {
        timeLeftText->setDefaultTextColor(QColor(Qt::red));
        sec->setDefaultTextColor(QColor(Qt::red));
    }
    timeLeftText->setPlainText(QString::number(countTime));
}

void FifthSceneDoctor::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfDoctor = 5;
    QSound::play(":/sounds/ComputerSciFi.wav");
    clear();
    deleteLater();
}

void FifthSceneDoctor::showResult() {
    footsteps->stop();
    removeItem(timeLeftText);
    removeItem(sec);

    if (response == 0) {
        setBackgroundBrush(QBrush(QImage(":/images2/OperationRoomDark2.jpg").scaledToWidth(1280).scaledToHeight(720)));
        box->setRect(40, 0, 1200, 80);
        addItem(enter);
        removeItem(exit);
        removeItem(character);
        story->setPlainText("You had to leave quickly because someone arrived.\nYou didn't have time to steal the medicine.");
        character->setPos(810, 340);
    }
    else if (response == 1) {
        box->setRect(490, 260, 300, 200);
        enter->setPos(740, 410);
        addItem(enter);
        story->setPos(495, 280);

        removeItem(exit);
        medicine->setPixmap(QPixmap(":/images2/MedicineGlow.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        story->setPlainText("You have decided to\nsteal the medicine.\nYour wife thanks you\nfor risking your job for her.");
        character->setPos(920, 400);
    }
    else if (response == 2) {
        box->setRect(490, 260, 300, 200);
        enter->setPos(740, 410);
        addItem(enter);
        story->setPos(495, 280);

        removeItem(medicine);
        exit->setPixmap(QPixmap(":/images2/ExitGlow.png").scaled(170, 170, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        story->setPlainText("You have decided to\nleave without stealing.\nYour wife understands your\nduty of following the rules.");
        character->setPos(810, 340);
    }
    enterState = 2;
}

void FifthSceneDoctor::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (clickState == 0)
        return;
    else if (clickState == 1) {
         QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
         if (item == medicine) {
            medicine->setPixmap(QPixmap(":/images2/MedicineGlow.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
         else if (item == exit) {
            exit->setPixmap(QPixmap(":/images2/ExitGlow.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         }
         else {
             medicine->setPixmap(QPixmap(":/images2/Medicine.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
             exit->setPixmap(QPixmap(":/images2/Exit.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         }
    }
}
