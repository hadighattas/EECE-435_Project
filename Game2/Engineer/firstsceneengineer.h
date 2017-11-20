#ifndef FIRSTSCENEENGINEER_H
#define FIRSTSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"
#include "../randomalien.h"

class FirstSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FirstSceneEngineer(QObject *parent = 0);
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
    int enterState;
};

#endif // FIRSTSCENEENGINEER_H
