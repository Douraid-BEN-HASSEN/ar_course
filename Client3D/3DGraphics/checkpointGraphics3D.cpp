#include "checkpointGraphics3D.h"

qreal CheckpointGraphics3D::radiusCheckpoint = 50;

CheckpointGraphics3D::CheckpointGraphics3D(Checkpoint *checkpoint, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->id = checkpoint->getId();
    this->x = checkpoint->getX();
    this->y = checkpoint->getY();
}

qreal CheckpointGraphics3D::getId()
{
    return id;
}

qreal CheckpointGraphics3D::getX()
{
    return x;
}

qreal CheckpointGraphics3D::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal CheckpointGraphics3D::getRadius()
{
    return radiusCheckpoint;
}

QRectF CheckpointGraphics3D::boundingRect() const
{
    return QRectF(-this->radiusCheckpoint, -this->radiusCheckpoint,this->radiusCheckpoint*2,this->radiusCheckpoint*2);

}

void CheckpointGraphics3D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    //painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
