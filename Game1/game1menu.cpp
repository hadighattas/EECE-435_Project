/**
 * \file game1menu.cpp
 * \brief Main Menu of the Game1
 *
 * Choosing level of difficulty.\n
 * Starting game.\n
*/

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
/**
 * @brief Game1Menu::changeCharacter
 */
void Game1Menu::changeCharacter(){
    /**
    * Changing character according to level of difficulty.\n
    */
    if(ui->easyRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background: transparent;background-image:url(./Shape4-500.png);border:0px;");
    }
    else if(ui->normalRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background: transparent;background-image:url(./Shape5-500.png);border:0px;");
    }
    else if(ui->hardRadioButton->isChecked()){
        ui->graphicsView->setStyleSheet("background: transparent;background-image:url(./Shape6-500.png);border:0px;");
    }
}
void Game1Menu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

/**
 * @brief Game1Menu::on_playButton_clicked
 */
void Game1Menu::on_playButton_clicked()
{
    /**
     * Creating the GraphicsView
     */
    int difficulty;
    Game1GraphicsView *game1graphicsview = new Game1GraphicsView;
    game1graphicsview->setStackedWidget(q);

    if(ui->easyRadioButton->isChecked()){
      difficulty = 0;
    }
    else if(ui->normalRadioButton->isChecked()){
       difficulty = 1;
    }
    else if(ui->hardRadioButton->isChecked()){
        difficulty = 2;
    }
    game1graphicsview->setDifficulty(difficulty);
    q->addWidget(game1graphicsview);
    q->setCurrentWidget(game1graphicsview);
}
