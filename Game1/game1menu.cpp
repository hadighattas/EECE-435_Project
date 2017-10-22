#include "game1menu.h"
#include "ui_game1menu.h"

Game1Menu::Game1Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1Menu)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(0);
}

Game1Menu::~Game1Menu()
{
    delete ui;
}

