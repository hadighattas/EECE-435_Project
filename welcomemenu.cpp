#include "welcomemenu.h"
#include "ui_welcomemenu.h"
#include "loginmenu.h"
#include "mainwindow.h"
#include "signupmenu.h"
#include "mainmenu.h"

WelcomeMenu::WelcomeMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeMenu)
{
    ui->setupUi(this);
}

// index of mainwindow in stackedWidget = 2
WelcomeMenu::~WelcomeMenu()
{
    delete ui;
}
void WelcomeMenu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}


void WelcomeMenu::on_loginButton_clicked()
{
    LoginMenu *loginmenu=new LoginMenu;
    loginmenu->setStackedWidget(q);
    q->addWidget(loginmenu);
    q->setCurrentWidget(loginmenu);
}

void WelcomeMenu::on_signupButton_clicked()
{
    SignUpMenu *signupmenu=new SignUpMenu;
    signupmenu->setStackedWidget(q);
    q->addWidget(signupmenu);
    q->setCurrentWidget(signupmenu);

}

void WelcomeMenu::on_guestButton_clicked()
{
    MainMenu *mainMenu = new MainMenu;
    mainMenu->setStackedWidget(q);
    q->addWidget(mainMenu);
    q->setCurrentWidget(mainMenu);
    string s="notify-send 'Hey how about signing up?' 'You could benefit from lots of user exclusive features!' '-t' 200";
    system(s.c_str());
}
