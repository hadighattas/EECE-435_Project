#include "game2score.h"
#include "ui_game2score.h"

Game2Score::Game2Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game2Score)
{
    ui->setupUi(this);
    ui->familyProgressBar->setValue(getPercentage(family));
    ui->friendshipProgressBar->setValue(getPercentage(friendship));
    ui->complianceProgressBar->setValue(getPercentage(compliance));
    ui->helpingProgressBar->setValue(getPercentage(helping));
    ui->honestyProgressBar->setValue(getPercentage(honesty));
    ui->courageProgressBar->setValue(getPercentage(courage));
    ui->forgivingnessProgressBar->setValue(getPercentage(forgivingness));
}

Game2Score::~Game2Score()
{
    delete ui;
}

int Game2Score::getPercentage(int value) {
    int temp = 50 + (value - 3) * 12;
    if (temp < 0)
        return 0;
    else if (temp > 100)
        return 100;
    return temp;
}
