#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    void setDifficulty(int diff);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

private:
    int difficulty;
};

#endif // PLAYER_H
