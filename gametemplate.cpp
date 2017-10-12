#include "gametemplate.h"
#include "ui_gametemplate.h"

GameTemplate::GameTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameTemplate)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(0);
}

GameTemplate::~GameTemplate()
{
    delete ui;
}

void GameTemplate::setGameName(QString game) {
    this->game = game;
    ui->gameLabel->setText(game);
}
