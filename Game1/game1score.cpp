#include "game1score.h"
#include "ui_game1score.h"
#include <QTextEdit>

Game1Score::Game1Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1Score)
{
    ui->setupUi(this);
}

Game1Score::~Game1Score()
{
    delete ui;
}

void Game1Score::setScore(int lives, int timeLeft, QStringList *finalValues, QStringList *finalVices) {
    this->lives = lives;
    this->timeLeft = timeLeft;
    this->finalValues = finalValues;
    this->finalVices = finalVices;

    ui->timeLeftValue->setText((std::to_string(timeLeft).c_str())+ ((QString)" seconds"));

    for (int i = 0; i < this->finalValues->length(); i++) {
        ui->textValues->append(this->finalValues->at(i) + '\n');
   //     ui->textValues->setTextColor(QColor(Qt::white));
    }

    for (int i = 0; i < this->finalVices->length(); i++)
        ui->textVices->append(this->finalVices->at(i) + '\n');

    for (int i = 0; i < lives; i++) {
        if( i == 0 )
            ui->graphicsView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 1 )
            ui->graphicsView_2->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 2 )
            ui->graphicsView_3->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 3 )
            ui->graphicsView_4->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 4 )
            ui->graphicsView_5->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 5 )
            ui->graphicsView_6->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
    }

    if((finalValues->size()*100 - finalVices->length()*150 + 5*timeLeft) < 0)
        score = 0;
    else
        score = finalValues->size()*100 - finalVices->length()*150 + 5*timeLeft;

    ui->scoreValue->setText(std::to_string(score).c_str());

    if(score > 300)
        ui->response->setText("Welcome to Earth!\n You have gained enough values to join us");
    else
        ui->response->setText("You have not gained enough values \nto join us on Earth :(");

    theUser->addGameScore(1, score);
}

void Game1Score::setStackedWidget(QStackedWidget *stack) {
    this->q = stack;
}

void Game1Score::on_exitButton_clicked()
{
    q->setCurrentIndex(mainIndex);
    q->show();
}
