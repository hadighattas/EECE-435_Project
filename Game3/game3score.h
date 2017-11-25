#ifndef GAME3SCORE_H
#define GAME3SCORE_H

#include <QWidget>
#include <QtWidgets>
#include <QStringList>
#include <string>

namespace Ui {
class Game3Score;
}

class Game3Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game3Score(QWidget *parent = 0);
    ~Game3Score();
    void setStackedWidget(QStackedWidget *stack);
    void setScore(int livesCount, QStringList *values, QStringList *vices);

private:
    Ui::Game3Score *ui;
    QStringList *finalValues, *finalVices;
    QStackedWidget *q;
    int lives;
    int score;
};

#endif // GAME3SCORE_H
