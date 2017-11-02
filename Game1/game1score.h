#ifndef GAME1SCORE_H
#define GAME1SCORE_H

#include <QWidget>

namespace Ui {
class Game1Score;
}

class Game1Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game1Score(QWidget *parent = 0);
    ~Game1Score();

private:
    Ui::Game1Score *ui;
};

#endif // GAME1SCORE_H
