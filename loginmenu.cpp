#include "loginmenu.h"
#include "ui_loginmenu.h"
#include"welcomemenu.h"
#include "mainmenu.h"
#include <cstring>
using namespace std;

LoginMenu::LoginMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginMenu)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

LoginMenu::~LoginMenu()
{
    delete ui;
}

void LoginMenu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

void LoginMenu::on_passwordLineEdit_returnPressed(){
    on_loginButton_clicked();
}

void LoginMenu::on_usernameLineEdit_returnPressed(){
    ui->passwordLineEdit->clear();
    ui->passwordLineEdit->setFocus();
}

void LoginMenu::on_loginButton_clicked()
{
    MainMenu *mainMenu = new MainMenu;
    mainMenu->setStackedWidget(q);
    q->addWidget(mainMenu);
    q->setCurrentWidget(mainMenu);
    string s="notify-send 'Welcome back "+ui->usernameLineEdit->text().toStdString()+"' 'You are now logged in' '-t' 200";
    system(s.c_str());
}

void LoginMenu::on_backButton_clicked()
{
    q->setCurrentIndex(2);
    q->show();
}
