#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcomemenu.h"
#include "firebasehandler.h"
#include<cstring>
#include<QString>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(QSize(1280,720));
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-image: url(MenuBackground.jpg); background-color:black;");
    FirebaseHandler *handler = new FirebaseHandler;
    handler->signIn(QString::fromStdString("hadighattas97@gmail.com"), QString::fromStdString("123456"));
    handler->signUp(QString::fromStdString("becharafayad@live.com"), QString::fromStdString("123456"));
    WelcomeMenu *welcomemenu=new WelcomeMenu(this);
    welcomemenu->setStackedWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(welcomemenu);
    ui->stackedWidget->setCurrentWidget(welcomemenu);
    setWindowTitle("EECE 435L");
}

MainWindow::~MainWindow()
{
    delete ui;
}
