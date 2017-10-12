#include "signupmenu.h"
#include "ui_signupmenu.h"
#include"welcomemenu.h"
#include "mainmenu.h"
#include<regex>
#include<cstring>
#include<QWidget>
#include <QString>


using namespace std;


SignUpMenu::SignUpMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpMenu)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confPasswordLineEdit->setEchoMode(QLineEdit::Password);
}

SignUpMenu::~SignUpMenu()
{
    delete ui;
}

void SignUpMenu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

bool SignUpMenu::validateEmail(QString email){

QRegularExpression regex("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$");
if(!regex.match(email).hasMatch())
{
    return false;
}
return true;
}
void SignUpMenu::on_emailLineEdit_textChanged(const QString &arg1)
{
    if(!this->validateEmail(arg1)) ui->emailValidateView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(/home/hadi/EECE-435_Project/Images/x.png)");
    else ui->emailValidateView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image:none");

}

void SignUpMenu::on_signupButton_clicked()
{
    MainMenu *mainMenu = new MainMenu;
    mainMenu->setStackedWidget(q);
    q->addWidget(mainMenu);
    q->setCurrentWidget(mainMenu);
    string s="notify-send 'Welcome "+ui->usernameLineEdit->text().toStdString()+"' 'You have successfully signed up.' '-t' 200";
    system(s.c_str());
}

void SignUpMenu::on_backButton_clicked()
{
    q->removeWidget(this);
    WelcomeMenu *welcomemenu=new WelcomeMenu;
    welcomemenu->setStackedWidget(q);
    q->addWidget(welcomemenu);
    q->setCurrentWidget(welcomemenu);
}
