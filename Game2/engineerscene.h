#ifndef ENGINEERSCENE_H
#define ENGINEERSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QList>
#include <QSound>

#include "firstsceneengineer.h"

class EngineerScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EngineerScene(QObject *parent = 0);
    void setStackedWidget(QStackedWidget *stack);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

private:
    QStackedWidget *q;
    QGraphicsPixmapItem *arrow;
    QGraphicsTextItem *next;
    QPushButton *nextButton;

};

#endif // ENGINEERSCENE_H
