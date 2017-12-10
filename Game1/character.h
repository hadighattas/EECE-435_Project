#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QStringList>
#include <QList>
#include "obstaclegroup.h"
#include "global.h"

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = 0);
    void setDifficulty(int diff);
    void keyPressEvent(QKeyEvent *event);
    QStringList *getValues();
    QStringList *getVices();
    void checkCollisions();

    bool started;

signals:

public slots:

private:
    int difficulty;
    QStringList *values = new QStringList;
    QStringList *vices = new QStringList;

};

#endif // CHARACTER_H
