#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <QWidget>
#include<QtWidgets>

namespace Ui {
class LoginMenu;
}

class LoginMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LoginMenu(QWidget *parent = 0);
    ~LoginMenu();
    void setStackedWidget(QStackedWidget *stack);


private slots:

    void on_passwordLineEdit_returnPressed();

    void on_usernameLineEdit_returnPressed();

    void on_loginButton_clicked();

    void on_backButton_clicked();

private:
    Ui::LoginMenu *ui;
    QStackedWidget *q;

};

#endif // LOGINMENU_H
