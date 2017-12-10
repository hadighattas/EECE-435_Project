/**
 * \file Game3menu.cpp
 * \brief Main Menu of the Game3
 *
 * Choosing level of difficulty.\n
 * Starting game.\n
*/

#include "game3menu.h"
#include "ui_game3menu.h"

Game3Menu::Game3Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game3Menu)
{
    ui->setupUi(this);
    ui->easyRadioButton->setChecked(true);
}

Game3Menu::~Game3Menu()
{
    delete ui;
}


void Game3Menu::on_hardRadioButton_clicked()
{
    changeCharacter();
}

void Game3Menu::on_easyRadioButton_clicked()
{
    changeCharacter();
}

void Game3Menu::on_normalRadioButton_clicked()
{
    changeCharacter();
}
/**
 * @brief Game3Menu::changeCharacter
 */
void Game3Menu::changeCharacter(){
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
void Game3Menu::setStackedWidget(QStackedWidget *stack){
    this->q = stack;
    this->menuIndex = stack->currentIndex();
}

/**
 * @brief Game3Menu::on_playButton_clicked
 */
void Game3Menu::on_playButton_clicked()
{
    /**
     * Setting difficulty according to button selected.\n
     * Creating the GraphicsView.
     */
    int difficulty;
    Game3GraphicsView *Game3graphicsview = new Game3GraphicsView;
    Game3graphicsview->setStackedWidget(q, this->menuIndex);

    if(ui->easyRadioButton->isChecked()){
      difficulty = 0;
    }
    else if(ui->normalRadioButton->isChecked()){
       difficulty = 1;
    }
    else if(ui->hardRadioButton->isChecked()){
        difficulty = 2;
    }
    Game3graphicsview->setDifficulty(difficulty);
    q->addWidget(Game3graphicsview);
    q->setCurrentWidget(Game3graphicsview);
    game3Index = q->indexOf(Game3graphicsview);
}

void Game3Menu::on_resumeButton_clicked()
{
    q->setCurrentIndex(game3Index);
}
