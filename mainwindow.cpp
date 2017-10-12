#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcomemenu.h"
#include<cstring>
#include<QString>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(QSize(1280,720));
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-image: url(/home/hadi/EECE-435_Project/Images/Background.jpg); background-color:black;");
    WelcomeMenu *welcomemenu=new WelcomeMenu(this);
    welcomemenu->setStackedWidget(ui->stackedWidget);
    ui->stackedWidget->insertWidget(20,welcomemenu);
    ui->stackedWidget->setCurrentWidget(welcomemenu);
    int x=ui->stackedWidget->currentIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
}
