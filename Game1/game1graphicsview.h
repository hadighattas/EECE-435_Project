#ifndef GAME1GRAPHICSVIEW_H
#define GAME1GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

#include "game1scene.h"

class Game1GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game1GraphicsView(QWidget *parent = 0);
    void setDifficulty(int diff);
    void setStackedWidget(QStackedWidget *stack);
    void resume();
    Game1Scene *getScene();

signals:

public slots:

private:
    int difficulty;
    QStackedWidget *q;
    Game1Scene *scene1;
};

#endif // GAME1GRAPHICSVIEW_H
