#ifndef THIRDSCENEENGINEER_H
#define THIRDSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class ThirdSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ThirdSceneEngineer(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:
    void rotatePhone();
    void updateSeconds();

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story, *secondsLeftText, *sec;
    QGraphicsPixmapItem *character;
    QGraphicsPixmapItem *enter, *phone;
    QGraphicsRectItem *option1, *option2;
    QGraphicsTextItem *option1Text, *option2Text;
    QTimer *secondsLeft;
    QPen pen;
    int countSeconds;
    int enterState, response;
    QSound *tick, *viber, *ringtone;
};

#endif // THIRDSCENEENGINEER_H
