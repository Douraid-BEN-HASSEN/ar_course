#include "GCheckpoint.h"


qreal GCheckpoint::radiusCheckpoint = 50;

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

qreal GCheckpoint::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal GCheckpoint::getRadius()
{
    return radiusCheckpoint;
}

QRectF GCheckpoint::boundingRect() const
{
    return QRectF(-this->radiusCheckpoint, -this->radiusCheckpoint,this->radiusCheckpoint*2,this->radiusCheckpoint*2);

}

void GCheckpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    //painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
