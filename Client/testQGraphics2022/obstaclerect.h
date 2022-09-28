#ifndef OBSTACLERECT_H
#define OBSTACLERECT_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include "Kart/Map/Obstacle.h"

class ObstacleRect : public QGraphicsObject
{
    Q_OBJECT
public:
    ObstacleRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ObstacleRect(Obstacle *, QGraphicsItem *parent = nullptr);

    int id() const;
    qreal getX();
    qreal getY();
    qreal getHeigth();
    qreal getWidth();

private:
    int mId;
    qreal x;
    qreal y;
    qreal heigth = 100;
    qreal width = 100;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, int x, int y, int heigth, int width);
};

#endif // OBSTACLERECT_H
