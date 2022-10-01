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
    static qreal radiusCheckpoint;
    GCheckpoint();
    GCheckpoint(Checkpoint *, QGraphicsItem *parent = nullptr);
    Checkpoint *getCheckpoint();

    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Checkpoint *checkpoint;
    qreal id;
    qreal x;
    qreal y;
};

#endif // GCHECKPOINT_H
