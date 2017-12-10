#ifndef ENGINEERGRAPHICSVIEW_H
#define ENGINEERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

#include "engineerscene.h"
#include "user.h"

class EngineerGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EngineerGraphicsView(QWidget *parent = 0);
    void setStackedWidget(QStackedWidget *stack);

signals:

public slots:

private:
    QStackedWidget *q;

};

#endif // ENGINEERGRAPHICSVIEW_H
