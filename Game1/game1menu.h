#ifndef GAME1MENU_H
#define GAME1MENU_H

#include <QWidget>

namespace Ui {
class Game1Menu;
}

class Game1Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Game1Menu(QWidget *parent = 0);
    ~Game1Menu();

private slots:
    void changeCharacter();

    void on_hardRadioButton_clicked();

    void on_easyRadioButton_clicked();

    void on_normalRadioButton_clicked();

private:
    Ui::Game1Menu *ui;
};

#endif // GAME1MENU_H
