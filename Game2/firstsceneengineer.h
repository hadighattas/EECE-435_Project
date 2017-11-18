#ifndef FIRSTSCENEENGINEER_H
#define FIRSTSCENEENGINEER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>
#include <QObject>

class FirstSceneEngineer : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit FirstSceneEngineer(QObject *parent = 0);

signals:

public slots:

};

#endif // FIRSTSCENEENGINEER_H
