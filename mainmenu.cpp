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
    this->q = stack;
}

void MainMenu::on_game1Button_clicked()
{
    Game1Menu *game1menu = new Game1Menu;
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
    Game3Menu *game3menu = new Game3Menu;
    game3menu->setStackedWidget(q);
    ui->stackedWidget_2->addWidget(game3menu);
    ui->stackedWidget_2->setCurrentWidget(game3menu);
}

void MainMenu::on_signOutButton_clicked()
{
    q->removeWidget(this);
    for(int i = q->count(); i >= 0; i--)
    {
        QWidget* widget = q->widget(i);
        q->removeWidget(widget);
        widget->deleteLater();
    }
    WelcomeMenu *welcomemenu = new WelcomeMenu;
    welcomemenu->setStackedWidget(q);
    q->addWidget(welcomemenu);
    q->setCurrentWidget(welcomemenu);
    string s="notify-send 'You have successfully logged out' 'See you soon!' '-t' 100";
    system(s.c_str());

}

void MainMenu::on_profileButton_clicked()
{
    Profile *profile = new Profile;
    ui->stackedWidget_2->addWidget(profile);
    ui->stackedWidget_2->setCurrentWidget(profile);

    theUser->averageGlobalScore(1);
    theUser->averageGlobalScore(2);
    theUser->averageGlobalScore(3);
}
