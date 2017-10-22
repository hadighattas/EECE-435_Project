#include "game1menu.h"
#include "ui_game1menu.h"
#include "game1graphicsview.h"

Game1Menu::Game1Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game1Menu)
{
    ui->setupUi(this);
    ui->easyRadioButton->setChecked(true);

}

Game1Menu::~Game1Menu()
{
    delete ui;
}


void Game1Menu::on_hardRadioButton_clicked()
{
    changeCharacter();
}

void Game1Menu::on_easyRadioButton_clicked()
{
    changeCharacter();
}

void Game1Menu::on_normalRadioButton_clicked()
{
    changeCharacter();
}
void Game1Menu::changeCharacter(){
    if(ui->easyRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background-image:url(./Shape4-500.png);border:0px;");
    }
    else if(ui->normalRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background-image:url(./Shape5-500.png);border:0px;");
    }
    else if(ui->hardRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background-image:url(./Shape6-500.png);border:0px;");
    }
}
void Game1Menu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

void Game1Menu::on_loginButton_clicked()
{
    Game1GraphicsView *game1graphicsview=new Game1GraphicsView;

    q->addWidget(game1graphicsview);
    q->setCurrentWidget(game1graphicsview);

}
