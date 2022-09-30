#include "GCheckpoint.h"

GCheckpoint::GCheckpoint(Checkpoint *checkpoint, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();
}

qreal GCheckpoint::getId()
{
    return id;
}

qreal GCheckpoint::getX()
{
    return x;
}

qreal GCheckpoint::getY()
{
    return y;
}

qreal GCheckpoint::getRadius()
{
    return radius;
}

QRectF GCheckpoint::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void GCheckpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
