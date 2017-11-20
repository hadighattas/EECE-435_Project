#include "engineergraphicsview.h"

EngineerGraphicsView::EngineerGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    // creating first scene
    EngineerScene *engineerScene = new EngineerScene;
    engineerScene->setStackedWidget(q);
    setScene(engineerScene);
    show();
}

void EngineerGraphicsView::setStackedWidget(QStackedWidget *stack) {
        this->q = stack;
}
