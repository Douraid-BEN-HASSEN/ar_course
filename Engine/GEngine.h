#ifndef GENGINE_H
#define GENGINE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class GEngine: public QWidget
{
    Q_OBJECT
public:
    GEngine(QWidget *parent = nullptr);
    ~GEngine();
private:
    // liste checkpoints
    // liste obstacles
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    QMap<int, ObstacleGraphics*> localObstacles;
    QMap<int, CheckpointGraphics*> localCheckpoint;
    QMap<QString, PlayerGraphics*> localPlayers;
};

#endif // GENGINE_H
