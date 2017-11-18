#include "engineerscene.h"

EngineerScene::EngineerScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("SpaceBackground.png").scaledToHeight(720).scaledToWidth(1280)));
    setSceneRect(0, 0, 1280, 720);

    arrow = new QGraphicsPixmapItem((QPixmap("arrow.png")).scaled(100, 100));
    arrow->setPos(960, 490);
    arrow->setRotation(8);
    addItem(arrow);

    next = new QGraphicsTextItem("START");
    next->setPos(970, 528);
    next->setRotation(8);
    next->setDefaultTextColor(QColor(Qt::black));
    next->setFont(QFont("asap condensed", 15, QFont::Bold, false));
    next->document()->setPageSize(QSizeF(100,100));
    addItem(next);

    QSound::play("ComputerSciFi.wav");
}

void EngineerScene::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

void EngineerScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) {
        FirstSceneEngineer *first = new FirstSceneEngineer;
        QGraphicsView *view = views().at(0);
        view->setScene(first);
    }
}
