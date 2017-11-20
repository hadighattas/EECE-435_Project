#ifndef SIXTHSCENEENGINEER_H
#define SIXTHSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "global2.h"

class SixthSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SixthSceneEngineer(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *phone;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2, *option3;
    QGraphicsTextItem *option1Text, *option2Text, *option3Text;
    QPen pen;
    int enterState, response;
    QSound *notification;
};

#endif // SIXTHSCENEENGINEER_H
