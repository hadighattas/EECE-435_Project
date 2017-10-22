#ifndef GAME1MENU_H
#define GAME1MENU_H

#include <QWidget>
#include<QtWidgets>


namespace Ui {
class Game1Menu;
}

class Game1Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Game1Menu(QWidget *parent = 0);
    ~Game1Menu();
    void setStackedWidget(QStackedWidget *stack);

private slots:
    void changeCharacter();

    void on_hardRadioButton_clicked();

    void on_easyRadioButton_clicked();

    void on_normalRadioButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::Game1Menu *ui;
    QStackedWidget *q;

};

#endif // GAME1MENU_H
