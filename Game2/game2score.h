#ifndef GAME2SCORE_H
#define GAME2SCORE_H

#include <QWidget>

#include "global2.h"

namespace Ui {
class Game2Score;
}

class Game2Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game2Score(QWidget *parent = 0);
    ~Game2Score();

private:
    Ui::Game2Score *ui;
    int getPercentage (int value);
};

#endif // GAME2SCORE_H
