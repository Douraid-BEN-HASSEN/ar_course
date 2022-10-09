#include "GObstacle.h"

#include <QBrush>

QString GObstacle::type = "GObstacle";

qreal GObstacle::heigth = 100;
qreal GObstacle::width = 100;
qreal GObstacle::radius = 100;

GObstacle::GObstacle(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->setProperty("type", this->type);

    this->id = obstacle->getId();
    this->obstacle = obstacle;
    this->x = obstacle->getX();
    this->y = obstacle->getY();

    if ((int)this->getId() % 2 == 1) {
        item = new QGraphicsRectItem(-this->heigth/2, -this->width/2, this->heigth, this->width);
    } else {
        item = new QGraphicsEllipseItem(-this->radius, -this->radius, this->radius*2, this->radius*2);
    }
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

bool GObstacle::isObscuredBy(const QGraphicsItem *item) const
{
    return item->isObscuredBy(item);
}

QPainterPath GObstacle::shape() const
{
    return item->shape();
}

QRectF GObstacle::boundingRect() const
{
    return item->boundingRect();
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
