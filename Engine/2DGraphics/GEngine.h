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
#include <typeinfo>

#include "GCheckpoint.h"
#include "GObstacle.h"
#include "GPlayer.h"
#include "GItem.h"

class GEngine: public QWidget
{
    Q_OBJECT
public:
    GEngine(QWidget *parent = nullptr);
    ~GEngine();

    GPlayer *getGPlayer(QString uuid);

    QGraphicsScene *getScene();

    void addObstacleGraphics(GObstacle *);
    void addCheckpointGraphics(GCheckpoint *);
    void addPlayerGraphics(GPlayer *);
    void addItemGraphics(GItem *);

    void updateCheckpoint(Checkpoint* pCheckpoint);
    void updateObstacle(Obstacle* pObstacle);
    void updatePlayer(Player* pPlayer);

    void removeItem(QGraphicsItem *);

    void fitInView();
private:
    // liste checkpoints
    // liste obstacles
    QGraphicsScene* mScene;
    QGraphicsView* mView;

protected:
    void resizeEvent(QResizeEvent *event);

};

#endif // GENGINE_H
