#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

    ui->textBrowser->setTextColor(QColor(Qt::white));
    ui->textBrowser_2->setTextColor(QColor(Qt::white));
    ui->textBrowser_3->setTextColor(QColor(Qt::white));

    for (int i = 0; i < theUser.getGame1Scores().size(); i++)
        ui->textBrowser->append(theUser.getGame1Scores().at(i) + "\n");
    for (int i = 0; i < theUser.getGame2Scores().size(); i++)
        ui->textBrowser_2->append(theUser.getGame2Scores().at(i) + "\n");
    for (int i = 0; i < theUser.getGame3Scores().size(); i++)
        ui->textBrowser_3->append(theUser.getGame3Scores().at(i) + "\n");
    ui->progressBar_2->setValue(theUser.averageGlobalScore(1));
    ui->progressBar_4->setValue(theUser.averageGlobalScore(2));
    ui->progressBar_6->setValue(theUser.averageGlobalScore(3));

    int avg1 = 0 , avg2 = 0 , avg3 = 0;

    for(int i = 0; i < theUser.getGame1Scores().length(); i++)
        avg1 += theUser.getGame1Scores().at(i).toInt();
    if (theUser.getGame1Scores().length() == 0)
        avg1 = 0;
    else
        avg1 /= theUser.getGame1Scores().length();

    for(int i = 0; i < theUser.getGame2Scores().length(); i++)
        avg2 += theUser.getGame2Scores().at(i).toInt();
    if (theUser.getGame2Scores().length() == 0)
        avg2 = 0;
    else
        avg2 /= theUser.getGame2Scores().length();

    for(int i = 0; i < theUser.getGame3Scores().length(); i++)
        avg3 += theUser.getGame3Scores().at(i).toInt();
    if (theUser.getGame3Scores().length() == 0)
        avg3 = 0;
    else
        avg3 /= theUser.getGame3Scores().length();

    ui->progressBar->setValue(avg1);
    ui->progressBar_3->setValue(avg2);
    ui->progressBar_5->setValue(avg3);
}

Profile::~Profile()
{
    delete ui;
}
