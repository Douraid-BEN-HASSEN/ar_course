#ifndef GENGINE_H
#define GENGINE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtMqtt/QtMqtt>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QHBoxLayout>

#include "GCheckpoint.h"
#include "GObstacle.h"
#include "GPlayer.h"

class GEngine: public QWidget
{
    Q_OBJECT
public:
    GEngine(QWidget *parent = nullptr);
    ~GEngine();

    void addCheckpoint(Checkpoint* pCheckpoint);
    void addObstacle(Obstacle* pObstacle);
    void addPlayer(Player* pPlayer);
    void updateCheckpoint(Checkpoint* pCheckpoint);
    void updateObstacle(Obstacle* pObstacle);
    void updatePlayer(Player* pPlayer);
    void updateGraphics();
    QList<QGraphicsItem*> collision(QGraphicsItem* pGItem);

private:
    // liste checkpoints
    // liste obstacles
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    QMap<int, GCheckpoint*> localCheckpoint;
    QMap<int, GObstacle*> localObstacles;
    QMap<QString, GPlayer*> localPlayers;

protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // GENGINE_H
