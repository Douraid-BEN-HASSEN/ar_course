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

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QMap<int, ObstacleGraphics*> localObstacles;
    QMap<int, CheckpointGraphics*> localCheckpoint;




private:
    Ui::Widget *ui;
    QGraphicsScene* mScene;
    QGraphicsView* mView;

public slots:
    void updateMap();


};
#endif // WIDGET_H
