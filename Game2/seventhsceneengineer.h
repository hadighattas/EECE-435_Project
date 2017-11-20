#ifndef SEVENTHSCENEENGINEER_H
#define SEVENTHSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "global2.h"

class SeventhSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SeventhSceneEngineer(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:
    void updateScene();

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *blindCharacter , *fire;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2;
    QGraphicsTextItem *option1Text, *option2Text;
    QPen pen;
    QTimer *timePassedTimer;
    QSound *fireAlarm, *fireSound;
    int enterState, response, timePassed;

};

#endif // SEVENTHSCENEENGINEER_H
