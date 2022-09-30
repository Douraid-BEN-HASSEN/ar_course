#ifndef GOBSTACLE_H
#define GOBSTACLE_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include <Kart/Map/Obstacle.h>

class GObstacle: public QGraphicsObject
{
public:
    GObstacle(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    GObstacle(Obstacle *, QGraphicsItem *parent = nullptr);

    static qreal heigth;
    static qreal width;
    static qreal radius;

    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getHeigth();
    qreal getWidth();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    qreal id;
    qreal x;
    qreal y;
    // Récupérer depuis /game/properties

};

#endif // GOBSTACLE_H
