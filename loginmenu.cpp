#include "loginmenu.h"
#include "ui_loginmenu.h"

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
    if (ui->usernameLineEdit->text().size() == 0 || ui->passwordLineEdit->text().size() == 0) {
        ui->message->setText("Please enter username and password");
        return;
    }
    bool result = user->login(ui->usernameLineEdit->text(), ui->passwordLineEdit->text());
    theUser = user;
    connect(user, SIGNAL(loginUserResult(bool)), this, SLOT(displayLoginResult(bool)));
}

void LoginMenu::displayLoginResult(bool success) {
    if (success) {
        MainMenu *mainMenu = new MainMenu;
        mainMenu->setStackedWidget(q);
        q->addWidget(mainMenu);
        q->setCurrentWidget(mainMenu);
        mainIndex = q->indexOf(mainMenu);
    }
    else
        ui->message->setText("Incorrect username or password");
}

void LoginMenu::on_backButton_clicked()
{
    q->setCurrentIndex(2);
    q->show();
}
