#ifndef GAMETEMPLATE_H
#define GAMETEMPLATE_H

#include <QWidget>
#include <QString>

namespace Ui {
class GameTemplate;
}

class GameTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit GameTemplate(QWidget *parent = 0);
    void setGameName(QString game);
    ~GameTemplate();

private slots:


private:
    Ui::GameTemplate *ui;
    QString game;
};

#endif // GAMETEMPLATE_H
