#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtMqtt/QtMqtt>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"
#include "PlayerGraphics.h"

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

private:
    QMap<int, ObstacleGraphics*> localObstacles;
    QMap<int, CheckpointGraphics*> localCheckpoint;
    QMap<QString, PlayerGraphics*> localPlayers;

    QGraphicsScene* mScene;
    QGraphicsView* mView;

private slots:
    void updateMap();
    void updateProperties();
    void updateGameMode();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAPWIDGET_H
