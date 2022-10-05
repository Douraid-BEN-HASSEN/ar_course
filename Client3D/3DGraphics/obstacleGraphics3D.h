#ifndef OBSTACLEGRAPH_H
#define OBSTACLEGRAPH_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Map/Obstacle.h>

class ObstacleGraphics3D : public QGraphicsObject
{
    Q_OBJECT
public:
    ObstacleGraphics3D(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ObstacleGraphics3D(Obstacle *, QGraphicsItem *parent = nullptr);

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

#endif // OBSTACLEGRAPH_H
