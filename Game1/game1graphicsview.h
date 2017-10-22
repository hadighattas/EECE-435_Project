#ifndef GAME1GRAPHICSVIEW_H
#define GAME1GRAPHICSVIEW_H

#include <QGraphicsView>

class Game1GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Game1GraphicsView(QWidget *parent = 0);
    void setDifficulty(int diff);

signals:

public slots:

private:
    int difficulty;

};

#endif // GAME1GRAPHICSVIEW_H
