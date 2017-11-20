#ifndef SECONDSCENEDOCTOR_H
#define SECONDSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class SecondSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SecondSceneDoctor(QObject *parent = 0);
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
    QGraphicsPixmapItem *character, *your_brother, *stranger;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2;
    QGraphicsTextItem *option1Text, *option2Text;
    QPen pen;
    int clickState, enterState, response;


};

#endif // SECONDSCENEDOCTOR_H
