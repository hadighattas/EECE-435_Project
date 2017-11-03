#ifndef GAME1SCORE_H
#define GAME1SCORE_H

#include <QWidget>
#include <QStringList>
#include <string>

namespace Ui {
class Game1Score;
}

class Game1Score : public QWidget
{
    Q_OBJECT

public:
    explicit Game1Score(QWidget *parent = 0);
    void setScore(int lives, int timeLeft, QStringList *finalValues, QStringList *finalVices);
    ~Game1Score();    

private:
    Ui::Game1Score *ui;
    QStringList *finalValues, *finalVices;
    int lives;
    int timeLeft;
    int score;
};

#endif // GAME1SCORE_H
