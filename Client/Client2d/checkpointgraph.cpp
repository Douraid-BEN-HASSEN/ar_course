#include "checkpointgraph.h"
#include <QBrush>


Checkpointgraph::Checkpointgraph(Checkpoint *checkpoint, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->id = checkpoint->id;
    this->x = checkpoint->x;
    this->y = checkpoint->y;
}

qreal Checkpointgraph::getId()
{
    return id;
}

qreal Checkpointgraph::getX()
{
    return x;
}

qreal Checkpointgraph::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal Checkpointgraph::getRadius()
{
    return radius;
}

QRectF Checkpointgraph::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void Checkpointgraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
