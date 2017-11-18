#include "mainmenu.h"
#include "ui_mainmenu.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

void MainMenu::on_game1Button_clicked()
{
    Game1Menu *game1menu =new Game1Menu;
    game1menu->setStackedWidget(q);
    ui->stackedWidget_2->addWidget(game1menu);
    ui->stackedWidget_2->setCurrentWidget(game1menu);

}

void MainMenu::on_game2Button_clicked()
{
    Game2Menu *game2menu = new Game2Menu;
    game2menu->setStackedWidget(q);
    ui->stackedWidget_2->addWidget(game2menu);
    ui->stackedWidget_2->setCurrentWidget(game2menu);
}

void MainMenu::on_game3Button_clicked()
{
    GameTemplate *gameTemplate=new GameTemplate;
    gameTemplate->setGameName(ui->game3Button->text());
    ui->stackedWidget_2->addWidget(gameTemplate);
    ui->stackedWidget_2->setCurrentWidget(gameTemplate);
}

void MainMenu::on_signOutButton_clicked()
{
    q->removeWidget(this);
    WelcomeMenu *welcomemenu=new WelcomeMenu;
    welcomemenu->setStackedWidget(q);
    q->addWidget(welcomemenu);
    q->setCurrentWidget(welcomemenu);
    string s="notify-send 'You have successfully logged out' 'See you soon!' '-t' 200";
    system(s.c_str());

}
