#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QGraphicsScene>
#include "character.h"

class Game1Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Game1Scene(QObject *parent = 0);
    void setDifficulty(int diff);

signals:

public slots:

private:
    int difficulty;
    Character *character = new Character;

};

#endif // GAME1SCENE_H
