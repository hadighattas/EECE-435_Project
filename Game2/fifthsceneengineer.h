#ifndef FIFTHSCENEENGINEER_H
#define FIFTHSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "global2.h"

class FifthSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FifthSceneEngineer(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();

signals:

public slots:

private:
    QGraphicsRectItem *box, *options;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *your_friend, *your_colleague;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2, *option3;
    QGraphicsTextItem *option1Text, *option2Text, *option3Text, *optionsText;
    QPen pen;
    int clickState, enterState;

};

#endif // FIFTHSCENEENGINEER_H
