#include "game3score.h"
#include "ui_game3score.h"

Game3Score::Game3Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game3Score)
{
    ui->setupUi(this);
}

Game3Score::~Game3Score()
{
    delete ui;
}

void Game3Score::setStackedWidget(QStackedWidget *stack, int menuIndex) {
    this->q = stack;
    this->menuIndex = menuIndex;
}
/**
 * @brief Game3Score::setScore
 * @param lives Number of lives left
 * @param finalValues QStringList of values gained
 * @param finalVices QStrindList of vices gained
 */
void Game3Score::setScore(int lives, QStringList *finalValues, QStringList *finalVices) {
    this->lives = lives;
    this->finalValues = finalValues;
    this->finalVices = finalVices;
    /**
     * @brief Adding the values to the score page
     */
    for (int i = 0; i < this->finalValues->length(); i++)
        ui->textValues->append(this->finalValues->at(i) + '\n');
    /**
     * @brief Adding the vices to the score page
     */
    for (int i = 0; i < this->finalVices->length(); i++)
        ui->textVices->append(this->finalVices->at(i) + '\n');
    /**
     * @brief Adding the lives to the score page
     */
    for (int i = 0; i < lives; i++) {
        if( i == 0 )
            ui->graphicsView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 1 )
            ui->graphicsView_2->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        else if ( i == 2 )
            ui->graphicsView_3->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(:/images2/Shape10-50.png)");
        }

    if((finalValues->size()*100 - finalVices->length()*200) < 0)
        score = 0;
    else
        score = finalValues->size()*100 - finalVices->length()*200;

    ui->scoreValue->setText(std::to_string(score).c_str());
    if(score>400)
        ui->response->setText("Welcome to Earth!\n You have gained enough values to join us");
    else
        ui->response->setText("You have not gained enough values \nto join us on Earth :(");

    theUser->addGameScore(3, score);
}

void Game3Score::on_exitButton_clicked()
{
    q->setCurrentIndex(menuIndex);
    q->show();
}
