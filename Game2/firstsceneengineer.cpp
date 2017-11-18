#include "firstsceneengineer.h"

FirstSceneEngineer::FirstSceneEngineer(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QImage("back.png").scaledToWidth(1280).scaledToHeight(720)));
    setSceneRect(0, 0, 1280, 720);
}
