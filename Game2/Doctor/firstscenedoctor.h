#ifndef FIRSTSCENEDOCTOR_H
#define FIRSTSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"
#include "../randomalien.h"

class FirstSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FirstSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void addAliens();

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
    int enterState;

};

#endif // FIRSTSCENEDOCTOR_H
