#ifndef CHECKPOINTGRAPH_H
#define CHECKPOINTGRAPH_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include "Kart/Map/Checkpoint.h"

class Checkpointgraph: public QGraphicsObject
{
     Q_OBJECT
public:
    Checkpointgraph();
    Checkpointgraph(Checkpoint *, QGraphicsItem *parent = nullptr);
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
    // Récupérer depuis /game/properties
    qreal radius = 50;

};

#endif // CHECKPOINTGRAPH_H
