#include "fifthsceneengineer.h"

FifthSceneEngineer::FifthSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("Cubicles.jpg").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);

    character = new QGraphicsPixmapItem(QPixmap("Shape11-400.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    character->setPos(1060, 470);
    addItem(character);

    your_friend = new QGraphicsPixmapItem(QPixmap("Friend.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    your_friend->setPos(90, 460);
    addItem(your_friend);

    your_colleague = new QGraphicsPixmapItem(QPixmap("Colleague.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    your_colleague->setPos(530, 465);
    addItem(your_colleague);

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
    options = new QGraphicsRectItem;
    optionsText = new QGraphicsTextItem;

    //setting text of story
    story = new QGraphicsTextItem("After the meeting, you go back to your office, happy as can be to be assigned such an important job.\nAll your colleagues congratulate you on your new position.");
    story->setDefaultTextColor(QColor(Qt::black));
    story->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
    story->setPos(80, 10);
    addItem(story);

    //adding enter symbol
    enter = new QGraphicsPixmapItem(QPixmap("enter-200.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    enter->setPos(1150, 30);
    addItem(enter);
}

void FifthSceneEngineer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        story->setPlainText("Your first task is to choose someone to assume a technical position in the space shuttle team.\nWho would you choose?");
        removeItem(enter);

        pen.setWidth(5);

        //adding options
        options->setBrush(Qt::white);
        options->setPen(pen);
        options->setRect(40, 140, 385, 110);
        addItem(options);

        //setting text of options
        optionsText->setPlainText("Your friend who really wants to prove himself\nbut is not qualified enough\nor\nA very well qualified colleague.");
        optionsText->setDefaultTextColor(QColor(Qt::black));
        optionsText->setFont(QFont("Super Webcomic Bros.", 13, QFont::Normal, false));
        optionsText->setPos(50, 150);
        addItem(optionsText);

        //adding first option
        option1->setBrush(Qt::white);
        option1->setPen(pen);
        option1->setRect(150, 420, 120, 50);
        addItem(option1);

        //setting text of first option
        option1Text->setPlainText("Friend");
        option1Text->setDefaultTextColor(QColor(Qt::black));
        option1Text->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
        option1Text->setPos(175, 430);
        addItem(option1Text);

        //adding second option
        option2->setBrush(Qt::white);
        option2->setPen(pen);
        option2->setRect(585, 420, 120, 50);
        addItem(option2);

        //setting text of second option
        option2Text->setPlainText("Colleague");
        option2Text->setDefaultTextColor(QColor(Qt::black));
        option2Text->setFont(QFont("Super Webcomic Bros.", 16, QFont::Normal, false));
        option2Text->setPos(595, 430);
        addItem(option2Text);
    }
}

void FifthSceneEngineer::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    if (item == your_friend) {
        engineerValues << "FRIENDSHIP";
        changeScene();
    }
    else if (item == your_colleague) {
        if (engineerValues.contains("FRIENDSHIP"))
                engineerValues.removeOne("FRIENDSHIP");
        changeScene();
    }
}

void FifthSceneEngineer::changeScene() {
    QGraphicsView *view = views().at(0);
    view->setScene((QGraphicsScene*)this->parent());
    stateOfEngineer = 6;
    QSound::play("ComputerSciFi.wav");
    clear();
}

void FifthSceneEngineer::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
     QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
     if (item == your_friend) {
         your_friend->setPixmap(QPixmap("FriendGlow.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
     }
     else if (item == your_colleague) {
         your_colleague->setPixmap(QPixmap("ColleagueGlow.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
     }
     else {
         your_friend->setPixmap(QPixmap("Friend.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
         your_colleague->setPixmap(QPixmap("Colleague.png").scaled(240, 240, Qt::KeepAspectRatio, Qt::SmoothTransformation));
     }
}
