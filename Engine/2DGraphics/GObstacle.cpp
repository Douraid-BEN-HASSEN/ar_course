#include "GObstacle.h"

#include <QBrush>

QString GObstacle::type = "GObstacle";

qreal GObstacle::heigth = 100;
qreal GObstacle::width = 100;
qreal GObstacle::radius = 100;

GObstacle::GObstacle(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->setProperty("type", this->type);

    this->obstacle = obstacle;

    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();
}

int GObstacle::getId()
{
    return id;
}

qreal GObstacle::getX()
{
    return x;
}

qreal GObstacle::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal GObstacle::getHeigth()
{
    return heigth;
}
qreal GObstacle::getWidth()
{
    return width;
}

qreal GObstacle::getRadius()
{
    return radius;
}

QPainterPath GObstacle::shape() const
{
    QPainterPath path;
    if (this->boundingRect().isNull())
        return path;

    if ((int)this->id % 2 == 1) {
        path.addRect(this->boundingRect());
    } else {
        path.addEllipse(this->boundingRect());
    }

    return path;
}

QRectF GObstacle::boundingRect() const
{

    if ((int)this->id % 2 == 1) {
        return QRectF(-this->width/2, -this->heigth/2, this->width, this->heigth);
    } else {
        return QRectF(-this->radius, -this->radius, this->radius*2, this->radius*2);
    }
}

void GObstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    if ((int)this->getId() % 2 == 1) {
        painter->drawRect(boundingRect());
    } else {
        painter->drawEllipse(boundingRect());
    }

    painter->setPen(Qt::black);
    painter->drawText(0, 0, QString::number(this->getId()));
}

Obstacle *GObstacle::getObstacle()
{
    return this->obstacle;
}
