#ifndef WELCOMEMENU_H
#define WELCOMEMENU_H

#include <QWidget>
#include<QtWidgets>
#include "user.h"
#include "globalindices.h"

namespace Ui {
class WelcomeMenu;
}

class WelcomeMenu : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeMenu(QWidget *parent = 0);
    ~WelcomeMenu();
    void setStackedWidget(QStackedWidget *stack);

private slots:
    void on_loginButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::WelcomeMenu *ui;
    QStackedWidget *q;

};

#endif // WELCOMEMENU_H
