#ifndef GAME1MENU_H
#define GAME1MENU_H

#include <QWidget>
#include <QtWidgets>
#include "game1graphicsview.h"
#include "user.h"
#include "../globalindices.h"


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

    void on_playButton_clicked();

    void on_resumeButton_clicked();

private:
    Ui::Game1Menu *ui;
    QStackedWidget *q;
    Game1GraphicsView *game1graphicsview;
    Game1Scene *scene;

signals:
    void resumeOrder();
};

#endif // GAME1MENU_H
