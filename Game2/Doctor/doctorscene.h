#ifndef DOCTORSCENE_H
#define DOCTORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QWidget>
#include <QtWidgets>
#include <QString>
#include <QList>
#include <QSound>
#include <QTime>
#include <stdlib.h>

#include "../global2.h"
#include "firstscenedoctor.h"
#include "secondscenedoctor.h"
#include "thirdscenedoctor.h"
#include "fourthscenedoctor.h"
#include "fifthscenedoctor.h"
#include "sixthscenedoctor.h"
//#include "seventhscenedoctor.h"
//#include "eigthscenedoctor.h"


class DoctorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DoctorScene(QObject *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
    void updateTime();

private:
    QGraphicsPixmapItem *arrow, *character;
    QGraphicsTextItem *time, *money, *next;
    QPushButton *nextButton;
    QTimer *timerTime;
    bool flag;
    bool playSound;

};

#endif // DOCTORSCENE_H
