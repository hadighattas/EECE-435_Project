#ifndef SEVENTHSCENEDOCTOR_H
#define SEVENTHSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class SeventhSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SeventhSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void secondScenario();

signals:

public slots:

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *nurse;
    QGraphicsPixmapItem *enter;
    QGraphicsRectItem *option1, *option2, *option3;
    QGraphicsTextItem *option1Text, *option2Text, *option3Text;
    QPen pen;
    int clickState, enterState;
    QSound *breakingSound;

};

#endif // SEVENTHSCENEDOCTOR_H
