#ifndef SIGNUPMENU_H
#define SIGNUPMENU_H
#include <cstring>
#include <QWidget>
#include <QtWidgets>
#include <QKeyEvent>
#include <regex>
#include <cstring>
#include <QWidget>
#include <QString>
#include <QTimer>

#include "user.h"
#include"welcomemenu.h"
#include "mainmenu.h"
#include "globalindices.h"
#include "OAuth/helper.h"
#include "OAuth/fbdemo.h"
#include <QJsonObject>
#include <QVariantMap>

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
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_emailLineEdit_textChanged(const QString &arg1);
    void on_signupButton_clicked();
    void on_backButton_clicked();
    void signUpFB();
    void fbFailed();
    void displaySignupResult(int);
    void on_usernameLineEdit_textChanged(const QString &arg1);

private:
    Ui::SignUpMenu *ui;
    QStackedWidget *q;
    User *user = new User;
    Helper helper;
    bool fbDisabled = false;
    bool userNameValid, emailValid = false;
};

#endif // SIGNUPMENU_H
