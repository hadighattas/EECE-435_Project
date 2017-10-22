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

private:
    Ui::Game1Menu *ui;
};

#endif // GAME1MENU_H
