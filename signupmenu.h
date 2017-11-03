#ifndef SIGNUPMENU_H
#define SIGNUPMENU_H
#include <cstring>
#include <QWidget>
#include <QtWidgets>
#include "user.h"

using namespace std;


namespace Ui {
class SignUpMenu;
}

class SignUpMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpMenu(QWidget *parent = 0);
    ~SignUpMenu();
    bool validateEmail(QString email);
    void setStackedWidget(QStackedWidget *stack);

private slots:


    void on_emailLineEdit_textChanged(const QString &arg1);

    void on_signupButton_clicked();

    void on_backButton_clicked();

private:
    Ui::SignUpMenu *ui;
    QStackedWidget *q;
};

#endif // SIGNUPMENU_H
