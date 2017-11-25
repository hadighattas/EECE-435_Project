#ifndef GAME3SCENE_H
#define GAME3SCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QKeyEvent>
#include <QWidget>
#include <QtWidgets>
#include <stdlib.h>
#include <QGraphicsRectItem>
#include <QSound>

#include "player.h"
#include "global3.h"
#include "game3score.h"

#define OPEN 1
#define CLOSED 2
#define REMOVED 3

class Game3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game3Scene(QObject *parent = 0);
    void setDifficulty(int diff);
    void setStackedWidget(QStackedWidget *stack);
    void placeCards();
    void setValues();
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void match();
    void notMatch();
    void endGame();

private:
    int difficulty, livesCount;
    QList <QGraphicsPixmapItem*> cards, lives;
    QList <QGraphicsTextItem*> values;
    QGraphicsTextItem *endMessage;
    QStringList *valuesAcquired;
    QStringList *vicesAcquired;
    QList <int> stateOfCard;
    QStackedWidget *q;
    QTimer *timerMatch, *timerNotMatch, *timerEndGame;
    Player *player;
    int position1, position2, valuesLeftCount;
    QSound *fail, *win, *correct, *wrong, *flip;
};

#endif // GAME3SCENE_H
