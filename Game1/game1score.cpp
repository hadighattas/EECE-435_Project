#include "game1score.h"
#include "ui_game1score.h"

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
