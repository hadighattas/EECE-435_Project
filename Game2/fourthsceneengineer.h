#ifndef FOURTHSCENEENGINEER_H
#define FOURTHSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "global2.h"

class FourthSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FourthSceneEngineer(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2;
    QGraphicsTextItem *option1Text, *option2Text;
    QPen pen;
    int enterState, response;
};

#endif // FOURTHSCENEENGINEER_H
