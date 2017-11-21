#ifndef GAME2SCORE_H
#define GAME2SCORE_H

#include <QWidget>
#include <QtWidgets>

#include "global2.h"

namespace Ui {
class Game2Score;
}

class Game2Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game2Score(QWidget *parent = 0);
    void setStackedWidget(QStackedWidget *stack);
    ~Game2Score();

private slots:
    void on_exitButton_clicked();

private:
    Ui::Game2Score *ui;
    QStackedWidget *q;
    int getPercentage (int value);
    int sum;
};

#endif // GAME2SCORE_H
