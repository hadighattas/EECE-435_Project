#ifndef SIXTHSCENEDOCTOR_H
#define SIXTHSCENEDOCTOR_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QSound>

#include "../global2.h"

class SixthSceneDoctor : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SixthSceneDoctor(QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void changeScene();
    void showResult();

signals:

public slots:
    void rotatePhone();

private:
    QGraphicsRectItem *box;
    QGraphicsTextItem *story;
    QGraphicsPixmapItem *character, *enter;
    QGraphicsPixmapItem *ente, *phone;
    QGraphicsRectItem *option1, *option2;
    QGraphicsTextItem *option1Text, *option2Text;
    QPen pen;
    QTimer *timerPhone;
    int enterState, response, count;
    QSound *viber, *ringtone;

};

#endif // SIXTHSCENEDOCTOR_H
