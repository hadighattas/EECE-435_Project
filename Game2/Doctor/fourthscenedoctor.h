#ifndef FOURTHSCENEDOCTOR_H
#define FOURTHSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class FourthSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FourthSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:
    void updateScene();

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *water;
    QGraphicsPixmapItem *enter;
    QGraphicsPixmapItem *records, *briefcase;
    QTimer *waterTimer;
    QPen pen;
    QSound *waterSound;
    int enterState, response, countTimer;
};

#endif // FOURTHSCENEDOCTOR_H
