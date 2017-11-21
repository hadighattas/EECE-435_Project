#ifndef FIFTHSCENEDOCTOR_H
#define FIFTHSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class FifthSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FifthSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:
    void updateScene();

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story, *timeLeftText, *sec;
    QGraphicsPixmapItem *character, *medicine, *exit;
    QGraphicsPixmapItem *enter;
    QPen pen;
    int clickState, enterState, response;
    QSound *footsteps;
    QTimer *timeLeft;
    int countTime;

};

#endif // FIFTHSCENEDOCTOR_H
