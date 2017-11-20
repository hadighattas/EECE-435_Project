#ifndef THIRDSCENEDOCTOR_H
#define THIRDSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"


class ThirdSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ThirdSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *money, *moneyStack;
    QGraphicsPixmapItem *enter;
    QPen pen;
    int enterState, response;

};

#endif // THIRDSCENEDOCTOR_H
