#ifndef ENGINEERSCENE_H
#define ENGINEERSCENE_H

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

#include "global2.h"
#include "firstsceneengineer.h"
#include "secondsceneengineer.h"
#include "thirdsceneengineer.h"
#include "fourthsceneengineer.h"
#include "fifthsceneengineer.h"

using namespace std;

class EngineerScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EngineerScene(QObject *parent = 0);
    void setStackedWidget(QStackedWidget *stack);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
    void updateTime();

private:
    QStackedWidget *q;
    QGraphicsPixmapItem *arrow, *character;
    QGraphicsTextItem *time, *money, *next;
    QPushButton *nextButton;
    QTimer *timerTime;
    bool flag;
    bool playSound;

};

#endif // ENGINEERSCENE_H
