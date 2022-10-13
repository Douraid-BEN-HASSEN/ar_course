#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtMqtt/QtMqtt>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <Kart/Player/Item.h>

#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"
#include "PlayerGraphics.h"

#include "ItemGraphics.h"
#include "BananaGraphics.h"
#include "BombGraphics.h"
#include "RocketGraphics.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QMap<int, ObstacleGraphics*> localObstacles;
    QMap<int, CheckpointGraphics*> localCheckpoint;
    QMap<QString, PlayerGraphics*> localPlayers;
    QList<ItemGraphics*> localItems;

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
