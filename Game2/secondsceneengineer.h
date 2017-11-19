#ifndef SECONDSCENEENGINEER_H
#define SECONDSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "global2.h"
#include "randomalien.h"

class SecondSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SecondSceneEngineer(QObject *parent = 0);
    void addAliens();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();

signals:

public slots:

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2, *option3;
    QGraphicsTextItem *option1Text, *option2Text, *option3Text;
    QPen pen;

};

#endif // SECONDSCENEENGINEER_H
