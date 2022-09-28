#include "obstaclegraph.h"

#include <QBrush>



ObstacleGraph::ObstacleGraph(Obstacle *obstacle, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->id = obstacle->id;
    this->x = obstacle->x;
    this->y = obstacle->y;
}


qreal ObstacleGraph::getId()
{
    return id;
}

qreal ObstacleGraph::getX()
{
    return x;
}

qreal ObstacleGraph::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal ObstacleGraph::getHeigth()
{
    return heigth;
}
qreal ObstacleGraph::getWidth()
{
    return width;
}

qreal ObstacleGraph::getRadius()
{
    return radius;
}

QRectF ObstacleGraph::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void ObstacleGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    if((int)this->getId() % 2 == 1){
        painter->drawRect(-this->getHeigth()/2,-this->getWidth()/2,this->heigth, this->width);
    } else {
        painter->drawEllipse(-this->getHeigth()/2,-this->getWidth()/2,this->radius*2, this->radius*2);
    }

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}

