#ifndef GAME3MENU_H
#define GAME3MENU_H

#include <QWidget>
#include <QtWidgets>

#include "game3graphicsview.h"
#include "../globalindices.h"

namespace Ui {
class Game3Menu;
}

class Game3Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Game3Menu(QWidget *parent = 0);
    ~Game3Menu();
    void setStackedWidget(QStackedWidget *stack);

private slots:
    void changeCharacter();

    void on_hardRadioButton_clicked();

    void on_easyRadioButton_clicked();

    void on_normalRadioButton_clicked();

    void on_playButton_clicked();

    void on_resumeButton_clicked();

private:
    Ui::Game3Menu *ui;
    QStackedWidget *q;
    int menuIndex;
};

#endif // GAME3MENU_H
