#ifndef GAME1SCORE_H
#define GAME1SCORE_H

#include <QWidget>
#include <QtWidgets>
#include <QStringList>
#include <string>
#include "../globalindices.h"

namespace Ui {
class Game1Score;
}

class Game1Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game1Score(QWidget *parent = 0);
    void setScore(int lives, int timeLeft, QStringList *finalValues, QStringList *finalVices);
    void setStackedWidget(QStackedWidget *stack);
    ~Game1Score();    

private slots:
    void on_exitButton_clicked();

private:
    Ui::Game1Score *ui;
    QStringList *finalValues, *finalVices;
    QStackedWidget *q;
    int lives;
    int timeLeft;
    int score;
};

#endif // GAME1SCORE_H
