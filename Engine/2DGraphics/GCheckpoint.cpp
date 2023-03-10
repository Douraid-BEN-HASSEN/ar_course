#include "GCheckpoint.h"


QString GCheckpoint::type = "GCheckpoint";
qreal GCheckpoint::radiusCheckpoint = 50;

GCheckpoint::GCheckpoint(Checkpoint *checkpoint, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->setProperty("type", this->type);

    this->checkpoint = checkpoint;
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();
}

Checkpoint *GCheckpoint::getCheckpoint()
{
    return this->checkpoint;
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

QPainterPath GCheckpoint::shape() const
{
    QPainterPath path;
    if (this->boundingRect().isNull())
        return path;

    path.addEllipse(this->boundingRect());

    return path;
}

QRectF GCheckpoint::boundingRect() const
{
    return QRectF(-this->radiusCheckpoint, -this->radiusCheckpoint, this->radiusCheckpoint*2, this->radiusCheckpoint*2);
}

void GCheckpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::green);
    //painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, QString::number(this->getId()));

}
