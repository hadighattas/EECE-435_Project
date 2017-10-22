#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = 0);
    void setDifficulty(int diff);

signals:

public slots:

private:
    int difficulty;

};

#endif // CHARACTER_H
