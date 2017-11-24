#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QKeyEvent>
#include <QWidget>
#include <QtWidgets>
#include <stdlib.h>
#include <QGraphicsRectItem>

#include "player.h"
#include "global3.h"

#define OPEN 1
#define CLOSED 2
#define REMOVED 3

class Game3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game3Scene(QObject *parent = 0);
    void setDifficulty(int diff);
    void endGame();
    void placeCards();
    void setValues();
    void setStackedWidget(QStackedWidget *stack);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void match();
    void notMatch();

private:
    int difficulty;
    QList <QGraphicsPixmapItem*> cards;
    QList <QGraphicsTextItem*> values;
    QList <int> stateOfCard;
    QStackedWidget *q;
    QTimer *timerMatch, *timerNotMatch;
    Player *player;
    int position1, position2;

};

#endif // GAME3SCENE_H
