#include "doctorgraphicsview.h"

DoctorGraphicsView::DoctorGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setFixedSize(1280, 720);
    setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
}

void DoctorGraphicsView::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
    // creating first scene
    DoctorScene *doctorScene = new DoctorScene;
    doctorScene->setStackedWidget(q);
    setScene(doctorScene);
    show();
}
