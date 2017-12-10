#include "game2score.h"
#include "ui_game2score.h"

Game2Score::Game2Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game2Score)
{
    sum = 0;
    ui->setupUi(this);
    ui->familyProgressBar->setValue(getPercentage(family));
    ui->friendshipProgressBar->setValue(getPercentage(friendship));
    ui->complianceProgressBar->setValue(getPercentage(compliance));
    ui->helpingProgressBar->setValue(getPercentage(helping));
    ui->honestyProgressBar->setValue(getPercentage(honesty));
    ui->courageProgressBar->setValue(getPercentage(courage));
    ui->forgivingnessProgressBar->setValue(getPercentage(forgivingness));
    if (stateOfEngineer == 8)
        ui->character->setStyleSheet("border: 0px;\nbackground:url(Shape11-400.png)");
    else if (stateOfDoctor == 8)
        ui->character->setStyleSheet("border: 0px;\nbackground:url(Shape12-400.png)");
    ui->moneyText->setText(QString::number(moneyGlobal));
    ui->textBrowser->setTextColor(QColor(Qt::white));
    if (sum >= 350)
        ui->textBrowser->setText("Congratulations!\nYou have accumulated enough values to join Earth!");
    else
        ui->textBrowser->setText("Unfortunately, you have not accumulated enough values to\npass the training.\nYou are not accepted on Earth :(");
    ui->money->setPixmap(QPixmap("Money.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->textBrowser->setFont(QFont("asap condensed", 18, QFont::Bold, false));
}

Game2Score::~Game2Score()
{
    delete ui;
}

void Game2Score::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

int Game2Score::getPercentage(int value) {
    int temp = 50 + (value - 3) * 12;
    if (temp < 0)
        return 0;
    else if (temp > 100) {
        sum += 100;
        return 100;
    }
    sum += temp;
    return temp;
}

void Game2Score::on_exitButton_clicked()
{
    q->setCurrentIndex(mainIndex);
    q->show();
}
