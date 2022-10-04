#ifndef CHECKPOINTGRAPH_H
#define CHECKPOINTGRAPH_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include <Kart/Map/Checkpoint.h>

class CheckpointGraphics: public QGraphicsObject
{
     Q_OBJECT
public:
    static qreal radiusCheckpoint;
    CheckpointGraphics();
    CheckpointGraphics(Checkpoint *, QGraphicsItem *parent = nullptr);
    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal id;
    qreal x;
    qreal y;

};

#endif // CHECKPOINTGRAPH_H
