#include "CheckpointGraphics.h"

CheckpointGraphics::CheckpointGraphics(Checkpoint *checkpoint, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();
}

qreal CheckpointGraphics::getId()
{
    return id;
}

qreal CheckpointGraphics::getX()
{
    return x;
}

qreal CheckpointGraphics::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal CheckpointGraphics::getRadius()
{
    return radius;
}

QRectF CheckpointGraphics::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void CheckpointGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
