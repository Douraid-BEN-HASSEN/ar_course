#ifndef WIDGET_H
#define WIDGET_H

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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

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
#endif // WIDGET_H
