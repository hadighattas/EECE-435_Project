#ifndef GAME3GRAPHICSVIEW_H
#define GAME3GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

#include "game3scene.h"

class Game3GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game3GraphicsView(QWidget *parent = 0);
    void setDifficulty(int diff);
    void setStackedWidget(QStackedWidget *stack);

signals:

public slots:

private:
    int difficulty;
    QStackedWidget *q;

};

#endif // GAME3GRAPHICSVIEW_H
