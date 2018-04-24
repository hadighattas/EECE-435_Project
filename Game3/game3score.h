#ifndef GAME3SCORE_H
#define GAME3SCORE_H

#include <QWidget>
#include <QtWidgets>
#include <QStringList>
#include <string>

#include "../globalindices.h"

namespace Ui {
class Game3Score;
}

class Game3Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game3Score(QWidget *parent = 0);
    ~Game3Score();
    void setStackedWidget(QStackedWidget *stack, int menuIndex);
    void setScore(int livesCount, QStringList *values, QStringList *vices);

private slots:
    void on_exitButton_clicked();

private:
    Ui::Game3Score *ui;
    QStringList *finalValues, *finalVices;
    QStackedWidget *q;
    int menuIndex;
    int lives;
    int score;
};

#endif // GAME3SCORE_H
