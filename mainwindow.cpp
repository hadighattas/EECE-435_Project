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
    ui->centralWidget->setStyleSheet("background-image: url(:/images2/MenuBackground.jpg); background-color:black;");
//    FirebaseHandler *handler = new FirebaseHandler;
//    handler->signUp(QString::fromStdString("morgane"), QString::fromStdString("ayle"), QString::fromStdString("morganea.97@hotmail.com"),
//                    QString::fromStdString("morgane"), QString::fromStdString("123456"), QString::fromStdString("20"),
//                    QString::fromStdString("Female"));
    WelcomeMenu *welcomemenu=new WelcomeMenu(this);
    welcomemenu->setStackedWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(welcomemenu);
    ui->stackedWidget->setCurrentWidget(welcomemenu);
    setWindowTitle("Aliens Vs Vices");
}

MainWindow::~MainWindow()
{
    delete ui;
}
