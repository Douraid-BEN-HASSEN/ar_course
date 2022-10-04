#include "checkpointGraphics3D.h"

qreal CheckpointGraphics::radiusCheckpoint = 50;

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
    return radiusCheckpoint;
}

QRectF CheckpointGraphics::boundingRect() const
{
    return QRectF(-this->radiusCheckpoint, -this->radiusCheckpoint,this->radiusCheckpoint*2,this->radiusCheckpoint*2);

}

void CheckpointGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    //painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
