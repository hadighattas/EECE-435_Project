#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QtWidgets>
#include "welcomemenu.h"
#include "Game1/game1menu.h"
#include "Game2/game2menu.h"
#include "Game3/game3menu.h"
#include "user.h"
#include "profile.h"
#include <cstring>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    void setStackedWidget(QStackedWidget *stack);
    ~MainMenu();

private slots:
    void on_game1Button_clicked();

    void on_game2Button_clicked();

    void on_game3Button_clicked();

    void on_signOutButton_clicked();

    void on_profileButton_clicked();

private:
    Ui::MainMenu *ui;
    QStackedWidget *q;
};

#endif // MAINMENU_H
