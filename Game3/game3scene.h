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
    void setStackedWidget(QStackedWidget *stack, int menuIndex);
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
    /**
     * @brief cards List of cards QGraphicsPixmapItem*
     */
    QList <QGraphicsPixmapItem*> cards;
    /**
     * @brief cards List of lives QGraphicsPixmapItem*
     */
    QList <QGraphicsPixmapItem*> lives;
    /**
     * @brief values List of QGraphicsSimpleTextItem* that contains the values/ vices to be displayed
     */
    QList <QGraphicsTextItem*> values;
    /**
     * @brief endMessage QGraphicsTextItem* that shows up at the end of the game
     */
    QGraphicsTextItem *endMessage;
    /**
     * @brief valuesAcquired QStringList that contains the values acquired
     */
    QStringList *valuesAcquired;
    /**
     * @brief vicesAcquired QStringList that contains the vices acquired
     */
    QStringList *vicesAcquired;
    /**
     * @brief stateOfCard QList of integers that conatains the state of each card
     */
    QList <int> stateOfCard;
    QStackedWidget *q;
    int menuIndex;
    /**
     * @brief timerMatch QTimer between the time the user matches 2 cards and they disappear.
     */
    QTimer *timerMatch;
    /**
     * @brief timerMatch QTimer between the time the user open 2 cards that don't match and they flip.
     */
    QTimer *timerNotMatch;
    /**
     * @brief timerMatch QTimer between the time the game ends and the score menu is displayed.
     */
    QTimer *timerEndGame;
    /**
     * @brief player The character.
     */
    Player *player;
    /**
     * @brief position1 Position of the first opened card
     */
    int position1;
    /**
     * @brief position2 Position of the second opened card
     */
    int position2;
    /**
     * @brief valuesLeftCount Number of values left in the game
     */
    int valuesLeftCount;
    QSound *fail, *win, *correct, *wrong, *flip;
};

#endif // GAME3SCENE_H
