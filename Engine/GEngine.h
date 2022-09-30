#ifndef GENGINE_H
#define GENGINE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QHBoxLayout>

#include "GCheckpoint.h"
#include "GObstacle.h"

class GEngine: public QWidget
{
    Q_OBJECT
public:
    GEngine(QWidget *parent = nullptr);
    ~GEngine();

    void addCheckpoint(Checkpoint* pCheckpoint);
    void addObstacle(Obstacle* pObstacle);
    void updateGraphics();

private:
    // liste checkpoints
    // liste obstacles
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    QMap<int, GCheckpoint*> localCheckpoint;
    QMap<int, GObstacle*> localObstacles;
    //QMap<QString, PlayerGraphics*> localPlayers;
};

#endif // GENGINE_H
