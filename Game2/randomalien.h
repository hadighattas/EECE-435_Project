#ifndef RANDOMALIEN_H
#define RANDOMALIEN_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class RandomAlien : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit RandomAlien(QObject *parent = 0);

signals:

public slots:

private:
    int randomNumber;
};

#endif // RANDOMALIEN_H
