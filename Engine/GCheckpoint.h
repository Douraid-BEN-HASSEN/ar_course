#ifndef GCHECKPOINT_H
#define GCHECKPOINT_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include <Kart/Map/Checkpoint.h>

class GCheckpoint: public QGraphicsObject
{
    Q_OBJECT
public:
    GCheckpoint();
    GCheckpoint(Checkpoint *, QGraphicsItem *parent = nullptr);

    qreal getId();
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

#endif // GCHECKPOINT_H
