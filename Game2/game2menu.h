#ifndef GAME2MENU_H
#define GAME2MENU_H

#include <QWidget>
#include <QtWidgets>
#include "engineergraphicsview.h"

namespace Ui {
class Game2Menu;
}

class Game2Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Game2Menu(QWidget *parent = 0);
    void setStackedWidget(QStackedWidget *stack);
    ~Game2Menu();

private slots:

    void on_engineerButton_clicked();

    void on_doctorButton_clicked();

private:
    Ui::Game2Menu *ui;
    QStackedWidget *q;
};

#endif // GAME2MENU_H
