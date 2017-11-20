#ifndef DOCTORGRAPHICSVIEW_H
#define DOCTORGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

#include "doctorscene.h"

class DoctorGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DoctorGraphicsView(QWidget *parent = 0);
    void setStackedWidget(QStackedWidget *stack);

signals:

public slots:

private:
    QStackedWidget *q;

};

#endif // DOCTORGRAPHICSVIEW_H
