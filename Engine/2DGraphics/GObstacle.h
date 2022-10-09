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

    static QString type;

    static qreal heigth;
    static qreal width;
    static qreal radius;

    int getId() ;
    qreal getX();
    qreal getY();
    qreal getHeigth();
    qreal getWidth();
    qreal getRadius();

    Obstacle *getObstacle();

    bool isObscuredBy(const QGraphicsItem *item) const;
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Obstacle *obstacle;
    int id;
    qreal x;
    qreal y;

    QGraphicsItem *item;
    // Récupérer depuis /game/properties

};

#endif // GOBSTACLE_H
