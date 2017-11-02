#ifndef GAME1GRAPHICSVIEW_H
#define GAME1GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

class Game1GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game1GraphicsView(QWidget *parent = 0);
    void setDifficulty(int diff);
    void setStackedWidget(QStackedWidget *stack);

signals:

public slots:

private:
    int difficulty;
    QStackedWidget *q;
};

#endif // GAME1GRAPHICSVIEW_H
