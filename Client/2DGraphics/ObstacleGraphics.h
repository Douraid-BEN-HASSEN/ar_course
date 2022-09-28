#ifndef OBSTACLEGRAPH_H
#define OBSTACLEGRAPH_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Map/Obstacle.h>

class ObstacleGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    ObstacleGraphics(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ObstacleGraphics(Obstacle *, QGraphicsItem *parent = nullptr);
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
    qreal heigth = 100;
    qreal width = 100;
    qreal radius = 50;
};

#endif // OBSTACLEGRAPH_H
