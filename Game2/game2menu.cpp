#include "game2menu.h"
#include "ui_game2menu.h"

Game2Menu::Game2Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game2Menu)
{
    ui->setupUi(this);
}

Game2Menu::~Game2Menu()
{
    delete ui;
}

void Game2Menu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

void Game2Menu::on_engineerButton_clicked()
{
    EngineerGraphicsView *engineerGV = new EngineerGraphicsView;
    engineerGV->setStackedWidget(q);
    q->addWidget(engineerGV);
    q->setCurrentWidget(engineerGV);
}

void Game2Menu::on_doctorButton_clicked()
{
    ;
}
